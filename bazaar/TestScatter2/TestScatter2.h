#ifndef _TestScatter2_TestScatter2_h
#define _TestScatter2_TestScatter2_h

#include <Scatter/Scatter.h>

using namespace Upp;

#define LAYOUTFILE <TestScatter2/TestScatter2.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS MyImages
#define IMAGEFILE <TestScatter2/TestScatter2.iml>
#include <Draw/iml_header.h>

class Tab1 : public WithTab1<ParentCtrl> {
public:

	typedef Tab1 CLASSNAME;

	Tab1();
};

Tab1::Tab1()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	Vector<XY> s1,s2;
	s1<<XY(10,14)<<XY(20,25)<<XY(30,29)<<XY(40,24)<<XY(50,36);
	s2<<XY(20,34)<<XY(30,45)<<XY(40,49)<<XY(50,44)<<XY(60,56);
	scatter1.AddSeries(s1,"series1");
	scatter1.AddSeries(s2,"series2",true,LtRed);
	scatter1.ShowInfo();	
}


//*******************************************************************************************

double funct1(double x){return (x*x);}
double funct2(double x){return (-x*x);}
double funct3(double x){return 0;}

class Tab2 : public WithTab2<ParentCtrl> {
public:

	typedef Tab2 CLASSNAME;

	Tab2();
};

Tab2::Tab2()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter2.SetRange(12,60);
	scatter2.SetXYMin(-6,-30);
	scatter2.SetMajorUnits(2,10);
	scatter2.PlotFunction(&funct3,"X Axis",Green,18);
	scatter2.PlotFunction(&funct1,"x^2", Color(28,85,255),6);	
	scatter2.PlotFunction(&funct2,"-X^2",LtRed);		
}

//*******************************************************************************************

XY para1(double t) {return XY(cos(2*M_PI*t),sin(2*M_PI*t));}
XY para2(double t) {return XY(0.5*cos(6*M_PI*t)+3*t-1, 1.5+0.5*sin(6*M_PI*t));}
XY para3(double t) {return XY(3+(0.5+t)*cos(6*M_PI*t),(0.5+t)*sin(6*M_PI*t));}
XY para4(double t) {return XY(0,-0.25+0.5*t);}
XY para5(double t) {return XY(-0.25+0.5*t,0);}

class Tab3 : public WithTab3<ParentCtrl> {
public:

	typedef Tab3 CLASSNAME;

	Tab3();
};

Tab3::Tab3()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter3.SetRange(7,4);
	scatter3.SetMajorUnits(0.5,0.5);
	scatter3.SetXYMin(-2,-2);
	scatter3.PlotParaFunction(para1,"Circle",Yellow,6,50);
	scatter3.PlotParaFunction(para2,"Coil",White,6,100);
	scatter3.PlotParaFunction(para3,"Spiral",Color::Color(56,170,255),6,150);
	scatter3.PlotParaFunction(para4,"VLine",LtRed,6,2);
	scatter3.PlotParaFunction(para5,"HLine",LtRed,6,2);	
	scatter3.SetAntialiasing();
}

//******************************************************************************************

class Tab4 : public WithTab4<ParentCtrl> {
public:

	typedef Tab4 CLASSNAME;

	Tab4();
};

Tab4::Tab4()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter4.SetRange(13,50);
	scatter4.SetMajorUnits(1,10);
	scatter4.SetXYMin(0,-20);
	scatter4.SetMouseHandling(true);
	Vector<XY> s1,s2;
	s1<<XY(1,-6)<<XY(2,-4)<<XY(3,2)<<XY(4,8)<<XY(5,8)<<XY(6,15)<<XY(7,20)<<XY(8,25)<<XY(9,14)<<XY(10,10)<<XY(11,3)<<XY(12,-11);
	scatter4.AddSeries(s1,"2005",true);
	
	s2<<XY(1,-12)<<XY(2,-7)<<XY(3,0)<<XY(4,2)<<XY(5,10)<<XY(6,18)<<XY(7,25)<<XY(8,26)<<XY(9,15)<<XY(10,12)<<XY(11,7)<<XY(12,-6);
	scatter4.AddSeries(s2,"2006",true,LtRed);
	
	scatter4.Graduation_FormatX(Scatter::MON);
	WString sl="Temperature [";
	sl.Cat(176);
	sl.Cat("C]");
	scatter4.SetLabelY(sl);
	scatter4.SetMarkStyle(1,Scatter::RECTANGLE);
	scatter4.SetMarkWidth(1,24);
}

//***************************************************************************************

class Tab5 : public WithTab5<ParentCtrl> {
public:

	typedef Tab5 CLASSNAME;

	Tab5();
	void Animate();
	void Start();
	void Stop();
	void Reset();
	void PgDown();
	void PgUp();
	void Plus();
	void Minus();
	double t;
};

Tab5::Tab5()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter5.SetRange(10,100);
	Vector<XY> s1, s2;
	scatter5.AddSeries(s1,"U-t",true,LtBlue,0,6);
	scatter5.AddSeries(s2,"I-t",true,LtRed,0,6);
	b1<<=(THISBACK(Start));
	b2<<=(THISBACK(Stop));
	b3<<=(THISBACK(Reset));
	b4<<=(THISBACK(PgDown));
	b5<<=(THISBACK(PgUp));
	b6<<=(THISBACK(Plus));
	b7<<=(THISBACK(Minus));
	t=0.0;
	b2.Disable();
	
}

void Tab5::Animate()
{
	scatter5.AddPoint(0,XY(t,50+20*sin(t)),false);
	scatter5.AddPoint(1,XY(t,50+30*cos(t)));
	t+=0.1;
	if((t-scatter5.GetXMin())>=scatter5.GetXRange()) scatter5.SetXYMin(scatter5.GetXMin()+10,0);
	
}

void Tab5::Start()
{
	SetTimeCallback(-100, THISBACK(Animate));
	b1.Disable();
	b2.Enable();
}

void Tab5::Stop()
{
	KillTimeCallback();
	b1.Enable();
	b2.Disable();
}

void Tab5::Reset()
{
	t=0;
	Vector<XY> s1, s2;
	scatter5.SetData(0,s1);
	scatter5.SetData(1,s2);
	scatter5.SetXYMin(0,0);	
}

void Tab5::PgDown()
{
	scatter5.SetXYMin(scatter5.GetXMin()-5,0);
	scatter5.Refresh();
}

void Tab5::PgUp()
{
	scatter5.SetXYMin(scatter5.GetXMin()+5,0);
	scatter5.Refresh();
}

void Tab5::Plus()
{
	scatter5.SetRange(scatter5.GetXRange()/2,100);
	scatter5.Refresh();
}

void Tab5::Minus()
{
	scatter5.SetRange(scatter5.GetXRange()*2,100);
	scatter5.Refresh();
}


//*******************************************************************************************

class Tab6 : public WithTab6<ParentCtrl> {
public:

	typedef Tab6 CLASSNAME;

	Tab6();
	
	void FormatX(String& s, int i, double d);	
};

Tab6::Tab6()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter6.SetRange(6,100);
	scatter6.SetMajorUnits(1,20);
	scatter6.ShowInfo();
	
	Vector<XY> s1;
	s1<<XY(log10(10.0),14)<<XY(log10(1e2),25)<<XY(log10(1e3),39)<<XY(log10(1e4),44)<<XY(log10(1e5),76);
	scatter6.AddSeries(s1,"series1");
	scatter6.cbModifFormatX=THISBACK(FormatX);
	scatter6.LogX();
}

void Tab6::FormatX(String& s, int i, double d)
{
	s=FormatDoubleExp(ipow10(int(d)),1);
}


//******************************************************************************************

class Tab7 : public WithTab7<ParentCtrl> {
public:
	static double f1(double x);
	typedef Tab7 CLASSNAME;
	
	Tab7();	
	
	void AddSeries();
	void RemoveLastSeries();
	void RemoveFirstSeries();	
	void RemoveAllSeries();
	
	void AddFunct();
	void RemoveFirstFunct();
	void RemoveLastFunct();
	void RemoveAllFSeries();
};

Tab7::Tab7()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	
	b1<<=THISBACK(AddSeries);
	b2<<=THISBACK(RemoveLastSeries);
	b3<<=THISBACK(RemoveFirstSeries);
	b4<<=THISBACK(RemoveAllSeries);
	b5<<=THISBACK(AddFunct);
	b6<<=THISBACK(RemoveLastFunct);
	b7<<=THISBACK(RemoveFirstFunct);
	b8<<=THISBACK(RemoveAllFSeries);
}

void Tab7::AddSeries()
{
	Vector<XY> s;
	ConvertInt ci;	
	int topIndex=(scatter7.GetPData().IsEmpty() ? 0 : (int)ci.Scan(scatter7.GetPLegend().Top().Mid(6))+1);
	double f=1+topIndex*1.1;	
	s<<XY(10,3*f)<<XY(30,7*f)<<XY(50,12*f)<<XY(70,10*f);
	scatter7.AddSeries(s,String("series")+AsString(topIndex),true);
} 

void Tab7::RemoveLastSeries()
{
	scatter7.RemoveSeries(scatter7.GetPData().GetCount()-1);
}

void Tab7::RemoveFirstSeries()
{
	scatter7.RemoveSeries(0);
}

void Tab7::RemoveAllSeries()
{
	scatter7.RemoveAllSeries();
}

double Tab7::f1(double x)
{
	return (25);
}

void Tab7::AddFunct()
{
	ConvertInt ci;	
	int topIndex=(scatter7.GetFData().IsEmpty() ? 0 : (int)ci.Scan(scatter7.GetFLegend().Top().Mid(5))+1);
	scatter7.PlotFunction(f1,String("funct")+AsString(topIndex));
}

void Tab7::RemoveFirstFunct()
{
	scatter7.RemoveFSeries(0);
}

void Tab7::RemoveLastFunct()
{
	scatter7.RemoveFSeries(scatter7.GetFData().GetCount()-1);
}

void Tab7::RemoveAllFSeries()
{
	scatter7.RemoveAllFSeries();
}

//******************************************************************************************

class Tab8 : public WithTab8<ParentCtrl> {
public:

	typedef Tab8 CLASSNAME;

	Tab8();
	void MyFormat(String& s, int i, double d)
	{
		s=Format("%Mon",fround(d)); 
		if (!s.IsEmpty())
			s << "\n2011";
	}
};

Tab8::Tab8()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter8.SetRange(13,50,20);
	scatter8.SetMajorUnits(1,10);
	scatter8.SetXYMin(0,-20, 1000);
	scatter8.SetMouseHandling(true, true);
	Vector<XY> s1,s2, s3;
	s1<<XY(1,-6)<<XY(2,-4)<<XY(3,2)<<XY(4,8)<<XY(5,8)<<XY(6,15)<<XY(7,20)<<XY(8,25)<<XY(9,14)<<XY(10,10)<<XY(11,3)<<XY(12,-11);;
	scatter8.AddSeries(s1,"Temperature",true).SetPattern(LINE_DASHED);
	
	s2<<XY(1,1010)<<XY(2,1012)<<XY(3,1015)<<XY(4,1013)<<XY(5,1017)<<XY(6,1018)<<XY(7,1010)<<XY(8,1007)<<XY(9,1003)<<XY(10,1001)<<XY(11,1000)<<XY(12,1002);
	scatter8.AddSeries(s2,"Pressure",true,LtRed).SetPattern("oooooo...ooo...o...ooo...").SetDataPrimaryY(1, false);
	scatter8.SetDrawY2Reticle();
	
	s3<<XY(1,-20)<<XY(2,-20)<<XY(2,-10)<<XY(3,-10)<<XY(3,0)<<XY(4,0)<<XY(4,10)<<XY(5,10)<<XY(5,20)<<XY(6,20)<<XY(6,30)<<XY(7,30)<<XY(7,20)<<XY(8,20)<<XY(8,10);
	scatter8.AddSeries(s3,"Device 1",true);
	
	scatter8.cbModifFormatX = THISBACK(MyFormat);
	scatter8.SetMaxZoom(40).SetMinZoom(2, 20);
	WString sl="Temperature [";
	sl.Cat(176);
	sl.Cat("C]");
	scatter8.SetLabelY(sl);
	scatter8.SetLabelY2("Pressure [mBar]");
	scatter8.SetMarkStyle(1,Scatter::RECTANGLE);
	scatter8.SetMarkWidth(1,24);
	scatter8.ShowInfo();	
}

//******************************************************************************************

class TestScatter2 : public WithTestScatter2Layout<TopWindow> {
	
	Tab1 tab1;
	Tab2 tab2;
	Tab3 tab3;
	Tab4 tab4;
	Tab5 tab5;
	Tab6 tab6;
	Tab7 tab7;
	Tab8 tab8;
		
	typedef TestScatter2 CLASSNAME;
	
public:
	
	TestScatter2();
	void Preview();
	void SavePNG();
	void SaveJPG();
	#ifdef PLATFORM_WIN32
	void SaveEMF();
	#endif
	void SaveClipboard();
};

#endif

