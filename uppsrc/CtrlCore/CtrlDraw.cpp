#include "CtrlCore.h"

namespace Upp {

#define LLOG(x)     // DLOG(x)
#define LTIMING(x)  // DTIMING(x)

bool Ctrl::globalbackpaint;
bool Ctrl::globalbackbuffer;

static void sCheckGuiLock()
{
	ASSERT_(ThreadHasGuiLock(), "Using GUI in non-main thread without GuiLock");
}

void Ctrl::RefreshFrame(const Rect& r) {
	sCheckGuiLock();
	GuiLock __; // Beware: Even if we have ThreadHasGuiLock ASSERT, we still can be the main thread!
	if(!IsOpen() || !IsVisible() || r.IsEmpty()) return;
	LTIMING("RefreshFrame");
	LLOG("RefreshRect " << Name() << ' ' << r);
	if(GuiPlatformRefreshFrameSpecial(r))
		return;
	if(!top && !IsDHCtrl()) {
		if(InFrame())
			parent->RefreshFrame(r + GetRect().TopLeft());
		else
			parent->Refresh(r + GetRect().TopLeft());
	}
	else {
		LLOG("WndInvalidateRect: " << r << ' ' << Name());
		LTIMING("RefreshFrame InvalidateRect");
		WndInvalidateRect(r);
	}
}

void Ctrl::Refresh0(const Rect& area) {
	RefreshFrame((area + GetView().TopLeft()) & GetView().Inflated(OverPaint()));
}

void Ctrl::Refresh(const Rect& area) {
	sCheckGuiLock();
	GuiLock __; // Beware: Even if we have ThreadHasGuiLock ASSERT, we still can be the main thread!
	if(fullrefresh || !IsVisible() || !IsOpen()) return;
	LLOG("Refresh " << Name() << ' ' <<  area);
	Refresh0(area);
}

void Ctrl::Refresh() {
	sCheckGuiLock();
	GuiLock __; // Beware: Even if we have ThreadHasGuiLock ASSERT, we still can be the main thread!
	if(fullrefresh || !IsVisible() || !IsOpen()) return;
	LLOG("Refresh " << Name() << " full:" << fullrefresh);
	if(!GuiPlatformSetFullRefreshSpecial())
		fullrefresh = true; // Needs to be set ahead because of possible MT ICall that can cause repaint during Refresh0
	Refresh0(Rect(GetSize()).Inflated(OverPaint()));
}

void Ctrl::Refresh(int x, int y, int cx, int cy) {
	Refresh(RectC(x, y, cx, cy));
}

void Ctrl::RefreshFrame(int x, int y, int cx, int cy) {
	RefreshFrame(RectC(x, y, cx, cy));
}

void Ctrl::RefreshFrame() {
	LLOG("RefreshFrame " << Name());
	RefreshFrame(Rect(GetRect().Size()).Inflated(overpaint));
}

void  Ctrl::ScrollRefresh(const Rect& r, int dx, int dy)
{
	sCheckGuiLock();
	GuiLock __; // Beware: Even if we have ThreadHasGuiLock ASSERT, we still can be the main thread!
	LLOG("ScrollRefresh " << r << " " << dx << " " << dy);
	if(!IsOpen() || !IsVisible() || r.IsEmpty()) return;
	int tdx = tabs(dx), tdy = tabs(dy);
	if(dx) WndInvalidateRect(RectC(dx >= 0 ? r.left : r.right - tdx, r.top - tdy, tdx, r.Height()));
	if(dy) WndInvalidateRect(RectC(r.left - tdx, dy >= 0 ? r.top : r.bottom - tdy, r.Width(), tdy));
}

bool Ctrl::AddScroll(const Rect& sr, int dx, int dy)
{
	GuiLock __;
	if(!top)
		return true;
	for(int i = 0; i < top->scroll.GetCount(); i++) {
		Scroll& sc = top->scroll[i];
		if(sc.rect == sr && sgn(dx) == sgn(sc.dx) && sgn(dy) == sgn(sc.dy)) {
			sc.dx += dx;
			sc.dy += dy;
			ScrollRefresh(sc.rect, sc.dx, sc.dy);
			return false;
		}
		if(sc.rect.Intersects(sr)) {
			sc.rect |= sr;
			sc.dx = sc.dy = 0;
			WndInvalidateRect(sc.rect);
			return true;
		}
	}
	Scroll& sc = top->scroll.Add();
	sc.rect = sr;
	sc.dx = dx;
	sc.dy = dy;
	ScrollRefresh(sc.rect, sc.dx, sc.dy);
	return false;
}

Rect  Ctrl::GetClippedView()
{
	GuiLock __;
	Rect sv = GetScreenView();
	Rect view = sv;
	Ctrl *q = parent;
	Ctrl *w = this;
	while(q) {
		view &= w->InFrame() ? q->GetScreenRect() : q->GetScreenView();
		w = q;
		q = q->parent;
	}
	return view - GetScreenRect().TopLeft();
}

void Ctrl::ScrollCtrl(Top *top, Ctrl *q, const Rect& r, Rect cr, int dx, int dy)
{
	if(top && r.Intersects(cr)) { // Uno: Contains -> Intersetcs
		Rect to = cr;
		GetTopRect(to, false);
		if(r.Intersects(cr.Offseted(-dx, -dy))) { // Uno's suggestion 06/11/26 Contains -> Intersetcs
			Rect from = cr.Offseted(-dx, -dy);
			GetTopRect(from, false);
			MoveCtrl *m = FindMoveCtrlPtr(top->move, q);
			if(m && m->from == from && m->to == to) {
				LLOG("ScrollView Matched " << from << " -> " << to);
				m->ctrl = NULL;
				return;
			}
		}

		if(r.Intersects(cr.Offseted(dx, dy))) { // Uno's suggestion 06/11/26 Contains -> Intersetcs
			Rect from = to;
			to = cr.Offseted(dx, dy);
			GetTopRect(to, false);
			MoveCtrl& m = top->scroll_move.Add(q);
			m.from = from;
			m.to = to;
			m.ctrl = q;
			LLOG("ScrollView Add " << UPP::Name(q) << from << " -> " << to);
			return;
		}
		cr &= r;
		if(!cr.IsEmpty()) {
			Refresh(cr);
			Refresh(cr + Point(dx, dy));
		}
	}
}

void  Ctrl::ScrollView(const Rect& _r, int dx, int dy)
{
	GuiLock __;
	LLOG("ScrollView " << _r << " " << dx << " " << dy);
#ifdef GUIPLATFORM_NOSCROLL
	LLOG("NOSCROLL");
	Refresh(_r);
#else
	if(IsFullRefresh() || !IsVisible())
		return;
	if(IsDHCtrl()) {
		Refresh(_r);
		return;
	}
	Size vsz = GetSize();
	dx = sgn(dx) * min(abs(dx), vsz.cx);
	dy = sgn(dy) * min(abs(dy), vsz.cy);
	Rect r = _r & vsz;
	LLOG("ScrollView2 " << r << " " << dx << " " << dy);
	Ctrl *w;
	for(w = this; w->parent; w = w->parent)
		if(w->InFrame()) {
			Refresh();
			return;
		}
	if(!w || !w->top) return;
	Rect view = InFrame() ? GetView() : GetClippedView();
	Rect sr = (r + view.TopLeft()) & view;
	sr += GetScreenRect().TopLeft() - w->GetScreenRect().TopLeft();
	if(w->AddScroll(sr, dx, dy))
		Refresh();
	else {
		LTIMING("ScrollCtrls1");
		Top *top = GetTopCtrl()->top;
		for(Ctrl *q = GetFirstChild(); q; q = q->GetNext())
			if(q->InView())
				ScrollCtrl(top, q, r, q->GetRect(), dx, dy);
		if(parent)
			for(Ctrl *q = parent->GetFirstChild(); q; q = q->GetNext())
				if(q->InView() && q != this)
					ScrollCtrl(top, q, r, q->GetScreenRect() - GetScreenView().TopLeft(), dx, dy);
	}
#endif
}

void  Ctrl::ScrollView(int x, int y, int cx, int cy, int dx, int dy) {
	ScrollView(RectC(x, y, cx, cy), dx, dy);
}

void  Ctrl::ScrollView(int dx, int dy) {
	ScrollView(Rect(GetSize()), dx, dy);
}

void  Ctrl::SyncScroll()
{
	GuiLock __;
	if(!top)
		return;
	Vector<Scroll> scroll = pick(top->scroll);
	top->scroll.Clear();
	if(IsFullRefresh())
		return;
	for(int i = 0; i < scroll.GetCount(); i++) {
		Scroll& sc = scroll[i];
		if(abs(sc.dx) > 3 * sc.rect.Width() / 4 || abs(sc.dy) > 3 * sc.rect.Height() / 4) {
			LLOG("Sync scroll Invalidate rect" << sc.rect);
			WndInvalidateRect(sc.rect);
		}
		else
		if(sc.dx || sc.dy) {
			LLOG("WndScrollView " << sc.rect);
			WndScrollView(sc.rect, sc.dx, sc.dy);
		}
	}
}

Rect Ctrl::GetOpaqueRect() const
{
	return IsTransparent() ? Rect(0, 0, 0, 0) : GetSize();
}

Rect Ctrl::GetVoidRect() const
{
	return Rect(0, 0, 0, 0);
}


#ifdef _DEBUG

struct sDrawLevelCheck {
	Draw&        w;
	int          lvl;
	const Ctrl  *q;

	void Check() {
		ASSERT_(lvl == w.GetCloffLevel(), "Draw::Begin/End mismatch for " + UPP::Name(q));
	}

	sDrawLevelCheck(Draw& w, const Ctrl *q) : w(w), lvl(w.GetCloffLevel()), q(q) {}
	// NOTE: Checking level in destructor is a bad idea because of exceptions
};

#define LEVELCHECK(w, q)    sDrawLevelCheck _x_(w, q)
#define DOLEVELCHECK        _x_.Check();
#else
#define LEVELCHECK(w, q)
#define DOLEVELCHECK
#endif
#if defined(flagWINGL) || defined(flagLINUXGL)
void Ctrl::CtrlPaint(SystemDraw& w, const Rect& clip) {
	GuiLock __;
	LEVELCHECK(w, this);
	LTIMING("CtrlPaint");
	
	Rect rect = GetRect().GetSize();
	Rect orect = rect.Inflated(overpaint);
	if(!IsShown() || orect.IsEmpty() || clip.IsEmpty() || !clip.Intersects(orect))
		return;
	
	w.PushContext();
	//glPushMatrix();
	ApplyTransform(TS_BEFORE_CTRL_PAINT);
		
	Ctrl *q;
	Rect view = rect;
	for(int i = 0; i < frame.GetCount(); i++) {
		LEVELCHECK(w, NULL);
		frame[i].frame->FramePaint(w, view);
		view = frame[i].view;
	}
	Rect oview = view.Inflated(overpaint);
	bool hasviewctrls = false;
	bool viewexcluded = false;
	
	for(q = firstchild; q; q = q->next)
		if(q->IsShown())
			if(q->InFrame()) {
				if(!viewexcluded && IsTransparent() && q->GetRect().Intersects(view)) {
					w.Begin();
					w.ExcludeClip(view);
					viewexcluded = true;
				}
				LEVELCHECK(w, q);
				Point off = q->GetRect().TopLeft();
				w.Offset(off);
				q->CtrlPaint(w, clip - off);
				w.End();
			}
			else
				hasviewctrls = true;

	if(viewexcluded)
		w.End();
	//DOLEVELCHECK;

	if(!oview.IsEmpty() && oview.Intersects(clip)) {
		LEVELCHECK(w, this);
		if(cliptobounds)
			w.Clip(overpaint ? oview : view);
		w.Offset(view.left, view.top);
		Paint(w);
		PaintCaret(w);
		w.End();
		
		if(hasviewctrls && !view.IsEmpty()) {
			Rect cl = clip & view;
			for(q = firstchild; q; q = q->next)
				if(q->IsShown() && q->InView()) {
					Rect rr(q->popup ? clip : cl);
					LEVELCHECK(w, q);
					Rect qr = q->GetRect();
					Point off = qr.TopLeft() + view.TopLeft();
					Rect ocl = cl - off;
					if(ocl.Intersects(Rect(qr.GetSize()).Inflated(overpaint))) {
						w.Offset(off);
						q->CtrlPaint(w, rr - off);
						w.End();
					}
				}
		}

		if(cliptobounds)
			w.End();
	}
	
	ApplyTransform(TS_AFTER_CTRL_PAINT);
	//glPopMatrix();
	w.PopContext();
	DOLEVELCHECK;
}
#else
void Ctrl::CtrlPaint(SystemDraw& w, const Rect& clip) {
	GuiLock __;
	LEVELCHECK(w, this);
	LTIMING("CtrlPaint");
	LLOG("=== CtrlPaint " << UPP::Name(this) << ", clip: " << clip << ", rect: " << GetRect() << ", view: " << GetView());
	Rect rect = GetRect().GetSize();
	Rect orect = rect.Inflated(overpaint);
	if(!IsShown() || orect.IsEmpty() || clip.IsEmpty() || !clip.Intersects(orect))
		return;
	Ctrl *q;
	Rect view = rect;
	for(int i = 0; i < frame.GetCount(); i++) {
		LEVELCHECK(w, NULL);
		frame[i].frame->FramePaint(w, view);
		view = frame[i].view;
	}
	Rect oview = view.Inflated(overpaint);
	bool hasviewctrls = false;
	bool viewexcluded = false;
	for(q = firstchild; q; q = q->next)
		if(q->IsShown()) {
			if(q->InFrame()) {
				if(!viewexcluded && IsTransparent() && q->GetRect().Intersects(view)) {
					w.Begin();
					w.ExcludeClip(view);
					viewexcluded = true;
				}
				LEVELCHECK(w, q);
				Point off = q->GetRect().TopLeft();
				w.Offset(off);
				q->CtrlPaint(w, clip - off);
				w.End();
			}
			else
				hasviewctrls = true;
		}
	if(viewexcluded)
		w.End();
	DOLEVELCHECK;
	if(!oview.IsEmpty()) {
		if(oview.Intersects(clip) && w.IsPainting(oview)) {
			LEVELCHECK(w, this);
			if(overpaint) {
				w.Clip(oview);
				w.Offset(view.left, view.top);
				Paint(w);
				PaintCaret(w);
				w.End();
				w.End();
			}
			else {
				w.Clipoff(view);
				Paint(w);
				PaintCaret(w);
				w.End();
			}
		}
	}
	if(hasviewctrls && !view.IsEmpty()) {
		Rect cl = clip & view;
		w.Clip(cl);
		for(q = firstchild; q; q = q->next)
			if(q->IsShown() && q->InView()) {
				LEVELCHECK(w, q);
				Rect qr = q->GetRect();
				Point off = qr.TopLeft() + view.TopLeft();
				Rect ocl = cl - off;
				if(ocl.Intersects(Rect(qr.GetSize()).Inflated(overpaint))) {
					w.Offset(off);
					q->CtrlPaint(w, ocl);
					w.End();
				}
			}
		w.End();
	}
	DOLEVELCHECK;
}
#endif

int sShowRepaint;

void Ctrl::ShowRepaint(int q)
{
	sShowRepaint = q;
}

void ShowRepaintRect(SystemDraw& w, const Rect& r, Color c)
{
	if(sShowRepaint) {
		w.DrawRect(r, c);
		SystemDraw::Flush();
		Sleep(sShowRepaint);
	}
}

bool Ctrl::PaintOpaqueAreas(SystemDraw& w, const Rect& r, const Rect& clip, bool nochild)
{
	GuiLock __;
	LTIMING("PaintOpaqueAreas");
	if(!IsShown() || r.IsEmpty() || !r.Intersects(clip) || !w.IsPainting(r))
		return true;
	Point off = r.TopLeft();
	Point viewpos = off + GetView().TopLeft();
	if(backpaint == EXCLUDEPAINT)
		return w.ExcludeClip(r);
	Rect cview = clip & (GetView() + off);
	for(Ctrl *q = lastchild; q; q = q->prev)
		if(!q->PaintOpaqueAreas(w, q->GetRect() + (q->InView() ? viewpos : off),
		                        q->InView() ? cview : clip))
			return false;
	if(nochild && (lastchild || GetNext()))
		return true;
	Rect opaque = (GetOpaqueRect() + viewpos) & clip;
	if(opaque.IsEmpty())
		return true;
#ifdef SYSTEMDRAW
	if(backpaint == FULLBACKPAINT && !dynamic_cast<BackDraw *>(&w))
#else
	if(backpaint == FULLBACKPAINT && !w.IsBack())
#endif
	{
		ShowRepaintRect(w, opaque, LtRed());
		BackDraw bw;
		bw.Create(w, opaque.GetSize());
		bw.Offset(viewpos - opaque.TopLeft());
		bw.SetPaintingDraw(w, opaque.TopLeft());
		{
			LEVELCHECK(bw, this);
			Paint(bw);
			PaintCaret(bw);
			DOLEVELCHECK;
		}
		bw.Put(w, opaque.TopLeft());
	}
	else {
		w.Clip(opaque);
		ShowRepaintRect(w, opaque, Green());
		w.Offset(viewpos);
		{
			LEVELCHECK(w, this);
			Paint(w);
			PaintCaret(w);
			DOLEVELCHECK;
		}
		w.End();
		w.End();
	}
	LLOG("Exclude " << opaque);
	return w.ExcludeClip(opaque);
}

inline int Area(const Rect& r)
{
	return r.GetHeight() * r.GetWidth();
}

void CombineArea(Vector<Rect>& area, const Rect& r)
{
	LTIMING("CombineArea");
	if(r.IsEmpty()) return;
	int ra = Area(r);
	for(int i = 0; i < area.GetCount(); i++) {
		Rect ur = r | area[i];
		int a = Area(ur);
		if(a < 2 * (ra + Area(area[i])) || a < 16000) {
			area[i] = ur;
			return;
		}
	}
	area.Add(r);
}

void Ctrl::GatherTransparentAreas(Vector<Rect>& area, SystemDraw& w, Rect r, const Rect& clip)
{
	GuiLock __;
	LTIMING("GatherTransparentAreas");
	Point off = r.TopLeft();
	Point viewpos = off + GetView().TopLeft();
	r.Inflate(overpaint);
	Rect notr = GetVoidRect();
	if(notr.IsEmpty())
		notr = GetOpaqueRect();
	notr += viewpos;
	if(!IsShown() || r.IsEmpty() || !clip.Intersects(r) || !w.IsPainting(r))
		return;
	if(notr.IsEmpty())
		CombineArea(area, r & clip);
	else {
		if(notr != r) {
			CombineArea(area, clip & Rect(r.left, r.top, notr.left, r.bottom));
			CombineArea(area, clip & Rect(notr.right, r.top, r.right, r.bottom));
			CombineArea(area, clip & Rect(notr.left, r.top, notr.right, notr.top));
			CombineArea(area, clip & Rect(notr.left, notr.bottom, notr.right, r.bottom));
		}
		for(Ctrl *q = firstchild; q; q = q->next) {
			Point qoff = q->InView() ? viewpos : off;
			Rect qr = q->GetRect() + qoff;
			if(clip.Intersects(qr))
				q->GatherTransparentAreas(area, w, qr, clip);
		}
	}
}

Ctrl *Ctrl::FindBestOpaque(const Rect& clip)
{
	GuiLock __;
	Ctrl *w = NULL;
	for(Ctrl *q = GetFirstChild(); q; q = q->GetNext()) {
		if(q->IsVisible() && GetScreenView().Contains(q->GetScreenRect())) {
			Rect sw = q->GetScreenView();
			if((q->GetOpaqueRect() + sw.TopLeft()).Contains(clip)) {
				w = q;
				Ctrl *h = q->FindBestOpaque(clip);
				if(h) w = h;
			}
			else
			if(q->GetScreenView().Contains(clip))
				w = q->FindBestOpaque(clip);
			else
			if(q->GetScreenRect().Intersects(clip))
				w = NULL;
		}
	}
	return w;
}

void Ctrl::ExcludeDHCtrls(SystemDraw& w, const Rect& r, const Rect& clip)
{
	GuiLock __;
	LTIMING("PaintOpaqueAreas");
	if(!IsShown() || r.IsEmpty() || !r.Intersects(clip) || !w.IsPainting(r))
		return;
	Point off = r.TopLeft();
	Point viewpos = off + GetView().TopLeft();
	if(dynamic_cast<DHCtrl *>(this)) {
		w.ExcludeClip(r);
		return;
	}
	Rect cview = clip & (GetView() + off);
	for(Ctrl *q = lastchild; q; q = q->prev)
		q->ExcludeDHCtrls(w, q->GetRect() + (q->InView() ? viewpos : off),
		                  q->InView() ? cview : clip);
}

void Ctrl::UpdateArea0(SystemDraw& draw, const Rect& clip, int backpaint)
{
	GuiLock __;
	LTIMING("UpdateArea");
	LLOG("========== UPDATE AREA " << UPP::Name(this) << ", clip: " << clip << " ==========");
	ExcludeDHCtrls(draw, GetRect().GetSize(), clip);
	if(globalbackbuffer) {
		CtrlPaint(draw, clip);
		LLOG("========== END (TARGET IS BACKBUFFER)");
		return;
	}
	if(backpaint == FULLBACKPAINT || globalbackpaint) {
		ShowRepaintRect(draw, clip, LtRed());
		BackDraw bw;
		bw.Create(draw, clip.GetSize());
		bw.Offset(-clip.TopLeft());
		bw.SetPaintingDraw(draw, clip.TopLeft());
		CtrlPaint(bw, clip);
		bw.Put(draw, clip.TopLeft());
		LLOG("========== END (FULLBACKPAINT)");
		return;
	}
	if(backpaint == TRANSPARENTBACKPAINT) {
		LLOG("TransparentBackpaint");
		Vector<Rect> area;
		GatherTransparentAreas(area, draw, GetRect().GetSize(), clip);
		for(int i = 0; i < area.GetCount(); i++) {
			Rect ar = area[i];
			LLOG("Painting area: " << ar);
			ShowRepaintRect(draw, ar, LtBlue());
			BackDraw bw;
			bw.Create(draw, ar.GetSize());
			bw.Offset(-ar.TopLeft());
			bw.SetPaintingDraw(draw, ar.TopLeft());
			CtrlPaint(bw, ar);
			bw.Put(draw, ar.TopLeft());
			if(!draw.ExcludeClip(ar)) {
				LLOG("========== END");
				return;
			}
		}
		PaintOpaqueAreas(draw, GetRect().GetSize(), clip);
		LLOG("========== END");
		return;
	}
	CtrlPaint(draw, clip);
	LLOG("========== END");
}

void SweepMkImageCache();

void Ctrl::UpdateArea(SystemDraw& draw, const Rect& clip)
{
	GuiLock __;
	if(IsPanicMode())
		return;
	RemoveFullRefresh();
	Point sp = GetScreenRect().TopLeft();
	Ctrl *b = FindBestOpaque(clip + sp);
	if(b) {
		Point p = b->GetScreenRect().TopLeft() - sp;
		draw.Offset(p);
		b->UpdateArea0(draw, clip.Offseted(-p), backpaint);
		draw.End();
	}
	else
		UpdateArea0(draw, clip, backpaint);
	SweepMkImageCache();
}

void Ctrl::RemoveFullRefresh()
{
	GuiLock __;
	fullrefresh = false;
	for(Ctrl *q = GetFirstChild(); q; q = q->GetNext())
		q->RemoveFullRefresh();
}

Ctrl *Ctrl::GetTopRect(Rect& r, bool inframe, bool clip)
{
	GuiLock __;
	if(!inframe) {
		if(clip)
			r &= Rect(GetSize());
		r.Offset(GetView().TopLeft());
	}
	if(parent) {
		r.Offset(GetRect().TopLeft());
		return parent->GetTopRect(r, InFrame(), clip);
	}
	return this;
}

void  Ctrl::DoSync(Ctrl *q, Rect r, bool inframe)
{
	GuiLock __;
	ASSERT(q);
	LLOG("DoSync " << UPP::Name(q) << " " << r);
	Ctrl *top = q->GetTopRect(r, inframe);
	if(top && top->IsOpen()) {
		top->SyncScroll();
		top->WndUpdate(r);
	}
}

void  Ctrl::Sync()
{
	GuiLock __;
	LLOG("Sync " << Name());
	if(top && IsOpen()) {
		LLOG("Sync UpdateWindow " << Name());
		SyncScroll();
		WndUpdate();
	}
	else
	if(parent)
		DoSync(parent, GetRect(), inframe);
	SyncCaret();
}

void Ctrl::Sync(const Rect& sr)
{
	GuiLock __;
	LLOG("Sync " << Name() << "   " << sr);
	DoSync(this, sr, true);
	SyncCaret();
}

void Ctrl::DrawCtrlWithParent(Draw& w, int x, int y)
{
	GuiLock __;
	if(parent) {
		Rect r = GetRect();
		Ctrl *top = parent->GetTopRect(r, inframe);
		w.Clip(x, y, r.Width(), r.Height());
		w.Offset(x - r.left, y - r.top);
		SystemDraw *ws = dynamic_cast<SystemDraw *>(&w);
		if(ws)
			top->UpdateArea(*ws, r);
		w.End();
		w.End();
	}
	else
		DrawCtrl(w, x, y);
}

void Ctrl::DrawCtrl(Draw& w, int x, int y)
{
	GuiLock __;
	w.Offset(x, y);
	
	SystemDraw *ws = dynamic_cast<SystemDraw *>(&w);
	if(ws)
		UpdateArea(*ws, GetRect().GetSize());

//	CtrlPaint(w, GetSize()); _DBG_
		
	w.End();
}

void Ctrl::SyncMoves()
{
	GuiLock __;
	if(!top)
		return;
	for(int i = 0; i < top->move.GetCount(); i++) {
		MoveCtrl& m = top->move[i];
		if(m.ctrl) {
			RefreshFrame(m.from);
			RefreshFrame(m.to);
		}
	}
	for(int i = 0; i < top->scroll_move.GetCount(); i++) {
		MoveCtrl& s = top->scroll_move[i];
		if(s.ctrl) {
			RefreshFrame(s.from);
			RefreshFrame(s.to);
		}
	}
	top->move.Clear();
	top->scroll_move.Clear();
}

Ctrl& Ctrl::BackPaintHint()
{
	GuiLock __;
	if(IsDecentMachine())
		BackPaint();
	return *this;
}

void  Ctrl::GlobalBackPaint(bool b)
{
	GuiLock __;
	globalbackpaint = b;
}

void  Ctrl::GlobalBackPaintHint()
{
	if(IsDecentMachine())
		GlobalBackPaint();
}

void Ctrl::GlobalBackBuffer(bool b)
{
	GuiLock __;
	globalbackbuffer = b;
}

}
