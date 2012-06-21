String WwwFormat(Time tm);

String MIMECharsetName(byte charset);

String UrlEncode(const char *s, const char *end);
String UrlEncode(const char *s, int len);
String UrlEncode(const String& s);
String UrlDecode(const char *s, const char *end);
String UrlDecode(const char *s, int len);
String UrlDecode(const String& s);

String Base64Encode(const char *s, const char *end);
String Base64Encode(const char *s, int len);
String Base64Encode(const String& data);
String Base64Decode(const char *s, const char *end);
String Base64Decode(const char *s, int len);
String Base64Decode(const String& data);

class IpAddrInfo {
	enum { COUNT = 32 };
	struct Entry {
		const char *host;
		const char *port;
		int         status;
		addrinfo   *addr;
	};
	static Entry     pool[COUNT];
	
	enum {
		EMPTY = 0, WORKING, CANCELED, RESOLVED, FAILED
	};

	String host, port;
	Entry *entry;
	Entry  exe[1];

	static void EnterPool();
	static void LeavePool();
	static auxthread_t auxthread__ Thread(void *ptr);

	void Start();

public:
	void      Start(const String& host, int port);
	bool      InProgress();
	bool      Execute(const String& host, int port);
	addrinfo *GetResult();
	void      Clear();

	IpAddrInfo();
	~IpAddrInfo()           { Clear(); }
};

struct SSLInfo {
	String  cipher;
	bool    cert_avail;
	bool    cert_verified; // Peer verification not yet working - this is always false
	String  cert_subject;
	String  cert_issuer;
	Date    cert_notbefore;
	Date    cert_notafter;
	int     cert_version;
	String  cert_serial;
};

enum { WAIT_READ = 1, WAIT_WRITE = 2, WAIT_IS_EXCEPTION, WAIT_ALL = 7 };

class TcpSocket {
	enum { BUFFERSIZE = 512 };
	enum { NONE, CONNECT, ACCEPT, SSL_CONNECTED };
	SOCKET                  socket;
	int                     mode;
	char                    buffer[BUFFERSIZE];
	char                   *ptr;
	char                   *end;
	bool                    is_eof;
	bool                    is_error;
	bool                    is_abort;
	bool                    ipv6;

	int                     timeout;
	int                     waitstep;
	int                     done;

	int                     global_timeout;
	int                     start_time;
#ifdef PLATFORM_WIN32
	int                     connection_start;
#endif

	int                     errorcode;
	String                  errordesc;
	
	struct SSL {
		virtual bool  Start() = 0;
		virtual bool  Wait(dword flags, int end_time) = 0;
		virtual int   Send(const void *buffer, int maxlen) = 0;
		virtual int   Recv(void *buffer, int maxlen) = 0;
		virtual void  Close() = 0;
		virtual dword Handshake() = 0;
		
		virtual ~SSL() {}
	};
	
	One<SSL>                ssl;
	One<SSLInfo>            sslinfo;
	String                  cert, pkey;
	bool                    asn1;

	struct SSLImp;
	friend struct SSLImp;

	static SSL *(*CreateSSL)(TcpSocket& socket);
	static SSL *CreateSSLImp(TcpSocket& socket);

	friend void  InitCreateSSL();
	friend class IpAddrInfo;

	int                     GetEndTime() const;
	bool                    RawWait(dword flags, int end_time);
	bool                    Wait(dword events, int end_time);
	SOCKET                  AcceptRaw(dword *ipaddr, int timeout_msec);
	bool                    Open(int family, int type, int protocol);
	int                     RawRecv(void *buffer, int maxlen);
	int                     Recv(void *buffer, int maxlen);
	int                     RawSend(const void *buffer, int maxlen);
	int                     Send(const void *buffer, int maxlen);
	bool                    RawConnect(addrinfo *info);
	void                    RawClose();

	void                    ReadBuffer(int end_time);
	int                     Get_();
	int                     Peek_();
	int                     Peek_(int end_time);
	int                     Peek(int end_time)          { return ptr < end ? *ptr : Peek_(end_time); }
	bool                    IsGlobalTimeout();

	void                    Reset();

	void                    SetSockError(const char *context, int code, const char *errdesc);
	void                    SetSockError(const char *context, const char *errdesc);
	void                    SetSockError(const char *context);

	static int              GetErrorCode();
	bool             WouldBlock();
	static void             Init();


public:
	Callback        WhenWait;
	
	enum { ERROR_GLOBAL_TIMEOUT = -1000000 };

	static String   GetHostName();
	
	int             GetDone() const                          { return done; }

	bool            IsOpen() const                           { return socket != INVALID_SOCKET; }
	bool            IsEof() const                            { return is_eof && ptr == end; }

	bool            IsError() const                          { return is_error; }
	void            ClearError()                             { is_error = false; errorcode = 0; errordesc.Clear(); }
	int             GetError() const                         { return errorcode; }
	String          GetErrorDesc() const                     { return errordesc; }

	void            Abort()                                  { is_abort = true; }
	bool            IsAbort() const                          { return is_abort; }
	void            ClearAbort()                             { is_abort = false; }
	
	SOCKET          GetSOCKET() const                        { return socket; }
	String          GetPeerAddr() const;

	void            Attach(SOCKET socket);
	bool            Connect(const char *host, int port);
	bool            Connect(IpAddrInfo& info);
	bool            Listen(int port, int listen_count, bool ipv6 = false, bool reuse = true);
	bool            Accept(TcpSocket& listen_socket);
	void            Close();
	void            Shutdown();

	void            NoDelay();
	void            Linger(int msecs);
	void            NoLinger()                               { Linger(Null); }
	
	bool            Wait(dword events);
	bool            WaitRead()                               { return Wait(WAIT_READ); }
	bool            WaitWrite()                              { return Wait(WAIT_WRITE); }

	int             Peek()                                   { return ptr < end ? *ptr : Peek_(); }
	int             Term()                                   { return Peek(); }
	int             Get()                                    { return ptr < end ? *ptr++ : Get_(); }
	int             Get(void *buffer, int len);
	String          Get(int len);

	int             Put(const char *s, int len);
	int             Put(const String& s)                     { return Put(s.Begin(), s.GetLength()); }

	bool            GetAll(void *buffer, int len);
	String          GetAll(int len);
	String          GetLine(int maxlen = 65536);

	bool            PutAll(const char *s, int len);
	bool            PutAll(const String& s);
	
	bool            StartSSL();
	bool            IsSSL() const                            { return ssl; }
	bool            SSLHandshake();
	void            SSLCertificate(const String& cert, const String& pkey, bool asn1);
	const SSLInfo  *GetSSLInfo() const                       { return ~sslinfo; }

	TcpSocket&      Timeout(int ms)                          { timeout = ms; return *this; }
	int             GetTimeout() const                       { return timeout; }
	TcpSocket&      GlobalTimeout(int ms);
	TcpSocket&      NoGlobalTimeout()                        { return GlobalTimeout(Null); }
	TcpSocket&      Blocking()                               { return Timeout(Null); }
	TcpSocket&      WaitStep(int ms)                         { waitstep = ms; return *this; }
	int             GetWaitStep() const                      { return waitstep; }

	TcpSocket();
	~TcpSocket()                                             { Close(); }
};

class SocketWaitEvent {
	Vector< Tuple2<int, dword> > socket;
	fd_set read[1], write[1], exception[1];

public:
	void  Clear()                                            { socket.Clear(); }
	void  Add(SOCKET s, dword events = WAIT_ALL)             { socket.Add(MakeTuple((int)s, events)); }
	void  Add(TcpSocket& s, dword events = WAIT_ALL)         { Add(s.GetSOCKET(), events); }
	int   Wait(int timeout);
	dword Get(int i) const;
	dword operator[](int i) const                            { return Get(i); }
	
	SocketWaitEvent();
};

struct HttpCookie : Moveable<HttpCookie> {
	String id;
	String value;
	String domain;
	String path;
	String raw;

	void Clear();
	bool Parse(const String& cookie);
};

struct HttpHeader {
	String                        first_line;
	String                        f1, f2, f3;
	VectorMap<String, String>     fields;
	VectorMap<String, HttpCookie> cookies;
	bool                          scgi;
	
	String operator[](const char *id) const                  { return fields.Get(id, Null); }
	String GetCookie(const char *id) const;

	bool   Response(String& protocol, int& code, String& reason) const;
	bool   Request(String& method, String& uri, String& version) const;
	
	String GetProtocol() const                               { return f1; }
	int    GetCode() const;
	String GetReason() const                                 { return f3; }
	
	String GetMethod() const                                 { return f1; }
	String GetURI() const                                    { return f2; }
	String GetVersion() const                                { return f3; }

	int64  GetContentLength() const;

	void   Clear();
	bool   ParseAdd(const String& hdrs);
	bool   Parse(const String& hdrs);
	bool   ParseSCGI(const String& scgi_hdr);

	bool   Read(TcpSocket& socket);
	
	HttpHeader()                                             { scgi = false; }

private:
	void   Add(const String& id, const String& value);
	HttpHeader(const HttpHeader&);
};

class HttpRequest : public TcpSocket {
	int          phase;
	String       data;
	int          count;

	HttpHeader   header;

	String       error;
	String       body;

	enum {
		DEFAULT_HTTP_PORT        = 80,
		DEFAULT_HTTPS_PORT       = 443
	};

	enum {
		METHOD_GET,
		METHOD_POST,
		METHOD_HEAD,
		METHOD_PUT,
	};

	int          max_header_size;
	int          max_content_size;
	int          max_redirects;
	int          max_retries;
	int          timeout;

	String       host;
	int          port;
	String       proxy_host;
	int          proxy_port;
	String       proxy_username;
	String       proxy_password;
	String       ssl_proxy_host;
	int          ssl_proxy_port;
	String       ssl_proxy_username;
	String       ssl_proxy_password;
	String       path;
	bool         ssl;

	int          method;
	String       accept;
	String       agent;
	bool         force_digest;
	bool         is_post;
	bool         std_headers;
	bool         hasurlvar;
	String       contenttype;
	String       username;
	String       password;
	String       digest;
	String       request_headers;
	String       postdata;
	VectorMap<String, HttpCookie> cookies;

	String       protocol;
	int          status_code;
	String       reason_phrase;
	
	int          start_time;
	int          retry_count;
	int          redirect_count;
	
	int          chunk;

	IpAddrInfo   addrinfo;
	int          bodylen;
	bool         gzip;	
	Zlib         z;

	void         Init();

	void         StartPhase(int s);
	void         Start();
	void         Dns();
	void         StartConnect();
	void         ProcessSSLProxyResponse();
	void         AfterConnect();
	void         StartRequest();
	bool         SendingData();
	bool         ReadingHeader();
	void         StartBody();
	bool         ReadingBody();
	void         ReadingChunkHeader();
	void         Finish();
	bool         IsRequestTimeout();
	void         CopyCookies();

	void         HttpError(const char *s);
	void         ContentOut(const void *ptr, int size);
	void         Out(const void *ptr, int size);

	String       CalculateDigest(const String& authenticate) const;

public:
	Callback2<const void *, int> WhenContent;
	Callback                     WhenStart;
	Callback                     WhenDo;

	HttpRequest&  MaxHeaderSize(int m)                   { max_header_size = m; return *this; }
	HttpRequest&  MaxContentSize(int m)                  { max_content_size = m; return *this; }
	HttpRequest&  MaxRedirect(int n)                     { max_redirects = n; return *this; }
	HttpRequest&  MaxRetries(int n)                      { max_retries = n; return *this; }
	HttpRequest&  RequestTimeout(int ms)                 { timeout = ms; return *this; }
	HttpRequest&  ChunkSize(int n)                       { chunk = n; return *this; }

	HttpRequest&  Method(int m)                          { method = m; return *this; }
	HttpRequest&  GET()                                  { return Method(METHOD_GET); }
	HttpRequest&  POST()                                 { return Method(METHOD_POST); }
	HttpRequest&  HEAD()                                 { return Method(METHOD_HEAD); }
	HttpRequest&  PUT()                                  { return Method(METHOD_PUT); }

	HttpRequest&  Host(const String& h)                  { host = h; return *this; }
	HttpRequest&  Port(int p)                            { port = p; return *this; }
	HttpRequest&  SSL(bool b = true)                     { ssl = b; return *this; }
	HttpRequest&  Path(const String& p)                  { path = p; return *this; }
	HttpRequest&  User(const String& u, const String& p) { username = u; password = p; return *this; }
	HttpRequest&  Digest()                               { force_digest = true; return *this; }
	HttpRequest&  Digest(const String& d)                { digest = d; return *this; }
	HttpRequest&  Url(const char *url);
	HttpRequest&  UrlVar(const char *id, const String& data);
	HttpRequest&  operator()(const char *id, const String& data) { return UrlVar(id, data); }
	HttpRequest&  PostData(const String& pd)              { postdata = pd; return *this; }
	HttpRequest&  PostUData(const String& pd)             { return PostData(UrlEncode(pd)); }
	HttpRequest&  Post(const String& data)                { POST(); return PostData(data); }
	HttpRequest&  Post(const char *id, const String& data);
	HttpRequest&  ClearPost()                             { PostData(Null); GET(); return *this; }

	HttpRequest&  Headers(const String& h)                { request_headers = h; return *this; }
	HttpRequest&  ClearHeaders()                          { return Headers(Null); }
	HttpRequest&  AddHeaders(const String& h)             { request_headers.Cat(h); return *this; }
	HttpRequest&  Header(const char *id, const String& data);

	HttpRequest&  Cookie(const HttpCookie& c);
	HttpRequest&  Cookie(const String& id, const String& value,
	                     const String& domain = Null, const String& path = Null);
	HttpRequest&  CopyCookies(const HttpRequest& r);

	HttpRequest&  StdHeaders(bool sh)                     { std_headers = sh; return *this; }
	HttpRequest&  NoStdHeaders()                          { return StdHeaders(false); }
	HttpRequest&  Accept(const String& a)                 { accept = a; return *this; }
	HttpRequest&  UserAgent(const String& a)              { agent = a; return *this; }
	HttpRequest&  ContentType(const String& a)            { contenttype = a; return *this; }

	HttpRequest&  Proxy(const String& host, int port)     { proxy_host = host; proxy_port = port; return *this; }
	HttpRequest&  Proxy(const char *p);
	HttpRequest&  ProxyAuth(const String& u, const String& p) {  proxy_username = u; proxy_password = p; return *this; }

	HttpRequest&  SSLProxy(const String& host, int port)     { ssl_proxy_host = host; ssl_proxy_port = port; return *this; }
	HttpRequest&  SSLProxy(const char *p);
	HttpRequest&  SSLProxyAuth(const String& u, const String& p) {  ssl_proxy_username = u; ssl_proxy_password = p; return *this; }

	bool         IsSocketError() const                    { return TcpSocket::IsError(); }
	bool         IsHttpError() const                      { return !IsNull(error) ; }
	bool         IsError() const                          { return IsSocketError() || IsHttpError(); }
	String       GetErrorDesc() const                     { return IsSocketError() ? TcpSocket::GetErrorDesc() : error; }
	void         ClearError()                             { TcpSocket::ClearError(); error.Clear(); }

	String       GetHeader(const char *id)                { return header[id]; }
	String       operator[](const char *id)               { return GetHeader(id); }
	String       GetRedirectUrl();
	int          GetContentLength();
	int          GetStatusCode() const                    { return status_code; }
	String       GetReasonPhrase() const                  { return reason_phrase; }

	const HttpHeader& GetHttpHeader() const               { return header; }
	String       GetCookie(const char *id)                { return header.GetCookie(id); }

	String       GetContent() const                       { return body; }
	String       operator~() const                        { return GetContent(); }
	operator     String() const                           { return GetContent(); }
	void         ClearContent()                           { body.Clear(); }

	enum Phase {
		BEGIN, START, DNS,
		SSLPROXYREQUEST, SSLPROXYRESPONSE, SSLHANDSHAKE,
		REQUEST, HEADER, BODY,
		CHUNK_HEADER, CHUNK_BODY, TRAILER,
		FINISHED, FAILED
	};

	bool    Do();
	int     GetPhase() const                      { return phase; }
	String  GetPhaseName() const;
	bool    InProgress() const                    { return phase != FAILED && phase != FINISHED; }
	bool    IsFailure() const                     { return phase == FAILED; }
	bool    IsSuccess() const                     { return phase == FINISHED && status_code >= 200 && status_code < 300; }

	String  Execute();

	void    New();
	
	HttpRequest();
	HttpRequest(const char *url);
	
	static void  Trace(bool b = true);
};

bool HttpResponse(TcpSocket& socket, bool scgi, int code, const char *phrase,
                  const char *content_type = NULL, const String& data = Null,
                  const char *server = NULL);
