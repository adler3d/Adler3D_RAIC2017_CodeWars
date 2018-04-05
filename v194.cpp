//#undef Adler
//#define QAP_DEBUG
#ifdef Adler
#ifndef CLANG_QAPLITE
#include "qaplite\QapLite.h"
#endif
#include "qaplite\TQapGameV2.inl"
#include "qaplite\perf_sys.inl"
#else
struct  QapClock{double MS(){return 0;}};
#define QAP_PERF(NAME)
#define QAP_PERF_CODE(CODE){CODE;}
#define NO_QAP_PERF_CODE(CODE){CODE;}
#endif

#define _ALLOW_KEYWORD_MACROS
#if(!defined(_DEBUG)&&!defined(Adler))
#ifndef QAP_MSVC
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wreorder"
#pragma warning(push,1)
#endif
#include <cstring>
#endif
#ifndef NOMINMAX
  #define NOMINMAX
#endif
#define private public
#define protected public
#include "MyStrategy.h"
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <stack>
#include <memory>
#include <thread>
#include <mutex>
using std::vector;
using std::string;
//#undef Adler
#ifdef Adler
  #ifndef QAP_LITE_H
  #include <Windows.h>
  #include <fstream>
  inline string IToS(const int&val){char c[16];_itoa_s(val,c,10);return string(c);}
  inline string FToS(const double&val){char c[64];if(abs(val)>1e9){_snprintf_s(c,32,32,"%e",val);}else{sprintf_s(c,"%f",val);}return string(c);}
  inline string FToS2(const double&val){char c[64];if(abs(val)>1e9){_snprintf_s(c,32,32,"%e",val);}else{sprintf_s(c,"%.2f",val);}return string(c);}
  static bool IsKeyDown(int vKey){int i=GetAsyncKeyState(vKey);return i<0;}
  #define KB_CODE(){auto mwta=game.getWizardMaxTurnAngle();if(IsKeyDown('Q'))move.setTurn(-mwta);if(IsKeyDown('E'))move.setTurn(+mwta);if(IsKeyDown('W'))move.setSpeed(+100);if(IsKeyDown('S'))move.setSpeed(-100);if(IsKeyDown('D'))move.setStrafeSpeed(+100);if(IsKeyDown('A'))move.setStrafeSpeed(-100);}
  static bool file_put_contents(const string&FN,const string&mem)
  {
    using namespace std;
    auto*f=fopen(FN.c_str(),"w+b");
    if(!f)return false;
    if(!mem.empty())fwrite(&mem[0],mem.size(),1,f);
    fclose(f);
    return true;
  };
  #endif
#else
  void KB_CODE(){}
  static bool file_put_contents(const string&FN,const string&mem){return true;}
  string file_get_contents(const string&fn){return "";}
#endif
  
#ifndef QAP_LITE_H
#define QapAssert(COND)if(!(COND))__debugbreak();
#define QapNoWay()__debugbreak();
#endif

#define DEF_PRO_SORT_BY_FIELD(sort_by_field,TYPE,FIELD)\
  struct t_help_struct_for_sort_vec_of_##TYPE##_by_##FIELD{\
    static int __cdecl cmp_func(const void*a,const void*b){return cmp(*(TYPE*)a,*(TYPE*)b);}\
    static int cmp(const TYPE&a,const TYPE&b){return a.FIELD-b.FIELD;}\
  };\
  static void sort_by_field(vector<TYPE>&arr){\
    if(arr.empty())return;\
    std::qsort(&arr[0],arr.size(),sizeof(TYPE),t_help_struct_for_sort_vec_of_##TYPE##_by_##FIELD::cmp_func);\
  }

#define PRO_FUNCGEN_GETP_BY_FIELD(rettype,getp,arr,field_type,field)\
  rettype*getp(field_type value)\
  {\
    rettype*p=nullptr;\
    for(int i=0;i<arr.size();i++){\
      auto&ex=arr[i];\
      if(ex.field!=value)continue;\
      QapAssert(!p);\
      p=&ex;\
    }\
    return p;\
  }

#define PRO_FUNCGEN_ADD_UNIQUE_OBJ_BY_FIELD_V2(rettype,adduni,arr,field_type,field)\
  rettype*adduni(field_type value)\
  {\
    rettype*p=nullptr;\
    for(int i=0;i<arr.size();i++){\
      auto&ex=arr[i];\
      if(ex.field!=value)continue;\
      QapAssert(!p);\
      p=&ex;\
    }\
    if(!p){p=&qap_add_back(arr);p->field=value;}\
    return p;\
  }

template<class TYPE,class FUNC>
int qap_minval_id_for_vec(vector<TYPE>&arr,FUNC func){
  if(arr.empty())return -1;
  decltype(func(arr[0],0)) val;int id=-1;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    auto tmp=func(ex,i);
    if(!i||tmp<val){
      val=tmp;id=i;
    }
  }
  return id;
}
template<class TYPE,class FUNC>
int qap_minval_id_for_vec(const vector<TYPE>&arr,FUNC func){
  if(arr.empty())return -1;
  decltype(func(arr[0],0)) val;int id=-1;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    auto tmp=func(ex,i);
    if(!i||tmp<val){
      val=tmp;id=i;
    }
  }
  return id;
}

template<class TYPE>
static void operator+=(vector<TYPE>&dest,const vector<TYPE>&arr){
  for(int i=0;i<arr.size();i++){
    dest.push_back(arr[i]);
  }
}

template<class TYPE>int qap_includes(const vector<TYPE>&arr,const TYPE&value){for(int i=0;i<arr.size();i++){if(arr[i]==value)return true;}return false;}

#define QAP_MINVAL_ID_OF_VEC(arr,code)qap_minval_id_for_vec(arr,[&](decltype(arr[0])&ex,int i){return code;})

template<class TYPE,class FUNC>void qap_foreach(TYPE&&arr,FUNC func){auto n=arr.size();for(int i=0;i<n;i++)func(arr[i],i);}
template<class TYPE,class FUNC>void qap_foreach(const TYPE&arr,FUNC func){auto n=arr.size();for(int i=0;i<n;i++)func(arr[i],i);}
#define QAP_FOREACH(arr,code)qap_foreach(arr,[&](decltype(arr[0])&ex,int i){code;})

#ifndef QAP_LITE_H
template<typename TYPE,size_t COUNT>inline size_t lenof(TYPE(&)[COUNT]){return COUNT;}

template<class TYPE,class FUNC>void clean_if(vector<TYPE>&Arr,FUNC&&Pred){int last=0;for(int i=0;i<Arr.size();i++){auto&ex=Arr[i];if(Pred(ex))continue;if(last!=i){auto&ax=Arr[last];ax=std::move(ex);}last++;}if(last==Arr.size())return;Arr.resize(last);}

template<class TYPE>static TYPE&qap_add_back(vector<TYPE>&arr){arr.resize(arr.size()+1);return arr.back();}
template<typename TYPE>TYPE Sign(TYPE value){return (value>0)?TYPE(+1):TYPE(value<0?-1:0);}

typedef double real;const real Pi=3.14159265;const real Pi2=Pi*2;const real PiD2=Pi/2;const real PiD4=Pi/4;
template<class TYPE>inline TYPE Clamp(const TYPE&v,const TYPE&a,const TYPE&b){return std::max(a,std::min(v, b));}
template<typename TYPE>inline TYPE Lerp(const TYPE&A,const TYPE&B,const real&v){return A+(B-A)*v;}

class vec2d{
public:
  real x;real y;
  vec2d():x(0.0),y(0.0) {}
  vec2d(const real&x,const real&y):x(x),y(y) {}
  vec2d(const vec2d&v):x(v.x),y(v.y) {}
public:
  vec2d&operator=(const vec2d&v){x=v.x;y=v.y;return *this;}
  vec2d operator+()const{return *this;}
  vec2d operator-()const{return vec2d(-x,-y);}
  vec2d&operator+=(const vec2d&v){x+=v.x;y +=v.y;return *this;}
  vec2d&operator-=(const vec2d&v){x-=v.x; y-=v.y;return *this;}
  vec2d&operator*=(const real&f){x*=f;y*=f;return *this;}
  vec2d&operator/=(const real&f){x/=f;y/=f;return *this;}
public:
  vec2d Rot(const vec2d&OX)const{real M=OX.Mag();return vec2d(((x*+OX.x)+(y*OX.y))/M,((x*-OX.y)+(y*OX.x))/M);}
  vec2d UnRot(const vec2d&OX)const{real M=OX.Mag();if(M==0.0f){return vec2d(0,0);};return vec2d(((x*OX.x)+(y*-OX.y))/M,((x*OX.y)+(y*+OX.x))/M);}
  vec2d Ort()const{return vec2d(-y,x);}
  vec2d Norm()const{if((x==0)&&(y==0)){return vec2d(0,0);}return vec2d(x/this->Mag(),y/this->Mag());}
  vec2d SetMag(const real&val)const{return this->Norm().Mul(vec2d(val,val));}
  vec2d Mul(const vec2d&v)const{return vec2d(x*v.x,y*v.y);}
  vec2d Div(const vec2d&v)const{return vec2d(v.x!=0?x/v.x:x,v.y!=0?y/v.y:y);}
  real GetAng()const{return atan2(y,x);}
  real Mag()const{return sqrt(x*x+y*y);}
  real SqrMag()const{return x*x+y*y;}
public:
  real dist_to(const vec2d&p)const{return vec2d(p.x-x,p.y-y).Mag();}
  real sqr_dist_to(const vec2d&p)const{return vec2d(p.x-x,p.y-y).SqrMag();}
  bool dist_to_point_less_that_r(const vec2d&p,real r)const{return vec2d(p.x-x,p.y-y).SqrMag()<r*r;}
public:
  static vec2d min(const vec2d&a,const vec2d&b){return vec2d(std::min(a.x,b.x),std::min(a.y,b.y));}
  static vec2d max(const vec2d&a,const vec2d&b){return vec2d(std::max(a.x,b.x),std::max(a.y,b.y));}
  static void comin(vec2d&a,const vec2d&b){a=min(a,b);}
  static void comax(vec2d&a,const vec2d&b){a=max(a,b);}
  static vec2d sign(const vec2d&p){return vec2d(Sign(p.x),Sign(p.y));}
public:
  inline static real dot(const vec2d&a,const vec2d&b){return a.x*b.x+a.y*b.y;}
  inline static real cross(const vec2d&a,const vec2d&b){return a.x*b.y-a.y*b.x;}
  vec2d fabs()const{return vec2d(::fabs(x),::fabs(y));}
  real max()const{return std::max(x,y);}
  real min()const{return std::min(x,y);}
};
vec2d operator+(const vec2d&u,const vec2d&v){return vec2d(u.x+v.x,u.y+v.y);}
vec2d operator-(const vec2d&u,const vec2d&v){return vec2d(u.x-v.x,u.y-v.y);}
vec2d operator*(const vec2d&u,const real&v){return vec2d(u.x*v,u.y*v);}
vec2d operator*(const real&u,const vec2d&v){return vec2d(u*v.x,u*v.y);}
bool operator==(const vec2d&u,const vec2d&v){return (u.x==v.x)&&(u.y==v.y);}
bool operator!=(const vec2d&u,const vec2d&v){return !(u==v);}

inline vec2d Vec2dEx(const real&ang,const real&mag){return vec2d(cos(ang)*mag,sin(ang)*mag);}


class vec2i
{
public:
public:
  typedef vec2i SelfClass;
public:
  int x;
  int y;
public:
public:
  vec2i():x(0),y(0) {}
  vec2i(int x,int y):x(x),y(y) {};
  friend vec2i operator*(int u,const vec2i&v)
  {
    return vec2i(u*v.x,u*v.y);
  }
  friend vec2i operator*(const vec2i&v,int u)
  {
    return vec2i(u*v.x,u*v.y);
  }
  friend vec2i operator/(const vec2i&v,int d)
  {
    return vec2i(v.x/d,v.y/d);
  }
  friend vec2i operator+(const vec2i&u,const vec2i&v)
  {
    return vec2i(u.x+v.x,u.y+v.y);
  }
  friend vec2i operator-(const vec2i&u,const vec2i&v)
  {
    return vec2i(u.x-v.x,u.y-v.y);
  }
  void operator+=(const vec2i&v)
  {
    x+=v.x;
    y+=v.y;
  }
  void operator-=(const vec2i&v)
  {
    x-=v.x;
    y-=v.y;
  }
  int SqrMag()
  {
    return x*x+y*y;
  }
  float Mag()
  {
    return sqrt(float(x*x+y*y));
  }
  operator vec2d()const
  {
    return vec2d(x,y);
  }
  vec2i operator+()const
  {
    return vec2i(+x,+y);
  }
  vec2i operator-()const
  {
    return vec2i(-x,-y);
  }
  friend bool operator==(const vec2i&u,const vec2i&v)
  {
    return (u.x==v.x)&&(u.y==v.y);
  }
  friend bool operator!=(const vec2i&u,const vec2i&v)
  {
    return (u.x!=v.x)||(u.y!=v.y);
  }
  static vec2i fromVec2d(const vec2d&v){return vec2i(int(v.x),int(v.y));}
  vec2i Ort()const{return vec2i(-y,x);}
  vec2i Mul(const vec2i&v)const{return vec2i(x*v.x,y*v.y);}
  static vec2i sign(const vec2i&p){return vec2i(Sign(p.x),Sign(p.y));}
  static vec2i sign(const vec2d&p){return vec2i(Sign(p.x),Sign(p.y));}
};

static vec2i tovec2i(const vec2d&p){return vec2i(p.x,p.y);}
#endif

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

using namespace model;
using namespace std;

static const auto VH=VehicleType::HELICOPTER;
static const auto VF=VehicleType::FIGHTER;
static const auto VT=VehicleType::TANK;
static const auto VA=VehicleType::ARRV;
static const auto VI=VehicleType::IFV;

struct t_map{
  typedef real t_elem;
  vector<t_elem> mem;
  int w;
  int h;
public:
  void fill(int value){for(int i=0;i<w*h;i++)mem[i]=value;}
public:
  static void set_to_def(t_elem&v){v=0;}
  t_elem&get(const vec2d&p){return get(p.x,p.y);}
  const t_elem&get(const vec2d&p)const{return get(p.x,p.y);}
  t_elem&get(const vec2i&p){return get(p.x,p.y);}
  const t_elem&get(const vec2i&p)const{return get(p.x,p.y);}
  t_elem&get_unsafe(int x,int y){return mem[x+y*w];}
  const t_elem&get_unsafe(int x,int y)const{return mem[x+y*w];}
  t_elem&get_unsafe(const vec2i&p){return mem[p.x+p.y*w];}
  const t_elem&get_unsafe(const vec2i&p)const{return mem[p.x+p.y*w];}
  t_elem&fail_id(){return sys_fail_id_const(*this);};
  template<class T>static t_elem&sys_fail_id_const(T&v){const T&ref=(const T&)v;return (t_elem&)ref.fail_id();};
  const t_elem&fail_id()const{static t_elem buff;set_to_def(buff);return buff;};
  t_elem&get(int x,int y){if(x<0||y<0)return fail_id();if(x<w&&y<h)return get_unsafe(x,y);return fail_id();}
  bool check(const vec2i&p)const{if(p.x<0||p.y<0||p.x+1>w||p.y+1>h)return false;return true;}
  const t_elem&get(int x,int y)const{if(x<0||y<0)return fail_id();if(x<w&&y<h)return get_unsafe(x,y);return fail_id();}
  int conv_vec_to_id(const vec2i&v)const{return v.x+v.y*w;}
  void init(vec2i wh){
    w=wh.x;h=wh.y;
    mem.resize(w*h);
  }
};

template<class t_elem>
struct t_map_v2{
  //typedef real t_elem;
  vector<t_elem> mem;
  int w;
  int h;
public:
  void fill(int value){for(int i=0;i<w*h;i++)mem[i]=value;}
public:
  static void set_to_def(t_elem&v){v.set_to_def();}
  t_elem&get(const vec2d&p){return get(p.x,p.y);}
  const t_elem&get(const vec2d&p)const{return get(p.x,p.y);}
  t_elem&get(const vec2i&p){return get(p.x,p.y);}
  const t_elem&get(const vec2i&p)const{return get(p.x,p.y);}
  t_elem&get_unsafe(int x,int y){return mem[x+y*w];}
  const t_elem&get_unsafe(int x,int y)const{return mem[x+y*w];}
  t_elem&get_unsafe(const vec2i&p){return mem[p.x+p.y*w];}
  const t_elem&get_unsafe(const vec2i&p)const{return mem[p.x+p.y*w];}
  t_elem&fail_id(){return sys_fail_id_const(*this);};
  template<class T>static t_elem&sys_fail_id_const(T&v){const T&ref=(const T&)v;return (t_elem&)ref.fail_id();};
  const t_elem&fail_id()const{static t_elem buff;set_to_def(buff);return buff;};
  t_elem&get(int x,int y){if(x<0||y<0)return fail_id();if(x<w&&y<h)return get_unsafe(x,y);return fail_id();}
  bool check(const vec2i&p)const{if(p.x<0||p.y<0||p.x+1>w||p.y+1>h)return false;return true;}
  const t_elem&get(int x,int y)const{if(x<0||y<0)return fail_id();if(x<w&&y<h)return get_unsafe(x,y);return fail_id();}
  int conv_vec_to_id(const vec2i&v)const{return v.x+v.y*w;}
  void init(vec2i wh){
    w=wh.x;h=wh.y;
    mem.resize(w*h);
  }
};

struct t_app{
  Player me;World world;Game game;Move move;
  vector<Facility> objs;
  vector<Vehicle> vehs;
  vector<Vehicle> oldvehs;
  vector<char> id2updated;
  int empty_group_id=1;
  bool no_wait=false;

  t_map termap;
  t_map wetmap;
  t_map vis_termap;
  t_map vis_wetmap;

  vector<int> id2vehid;
  vector<int> id2oldvehid;
  vector<int> id2groupid;

  PRO_FUNCGEN_GETP_BY_FIELD(Facility,id2obj,objs,int,id);

  #define PRO_FUNCGEN_GETP_BY_ID(rettype,getp,arr,field_type,value,id2id)\
    rettype*getp(field_type value){auto tmp=id2id[value];if(tmp<0)return nullptr;return &arr[tmp];}
  //

  PRO_FUNCGEN_GETP_BY_ID(Vehicle,id2veh,vehs,int,id,id2vehid);
  PRO_FUNCGEN_GETP_BY_ID(Vehicle,id2oldvehs,oldvehs,int,id,id2oldvehid);
  real get_speed_factor(WeatherType t){
    if(t==WeatherType::CLEAR)return game.clearWeatherSpeedFactor;
    if(t==WeatherType::CLOUD)return game.cloudWeatherSpeedFactor;
    if(t==WeatherType::RAIN)return game.rainWeatherSpeedFactor;
    return 1.0;
  }
  real get_speed_factor(TerrainType t){
    if(t==TerrainType::PLAIN)return game.plainTerrainSpeedFactor;
    if(t==TerrainType::FOREST)return game.forestTerrainSpeedFactor;
    if(t==TerrainType::SWAMP)return game.swampTerrainSpeedFactor;
    return 1.0;
  }
  real get_vision_factor(WeatherType t){
    if(t==WeatherType::CLEAR)return game.clearWeatherVisionFactor;
    if(t==WeatherType::CLOUD)return game.cloudWeatherVisionFactor;
    if(t==WeatherType::RAIN)return game.rainWeatherVisionFactor;
    return 1.0;
  }
  real get_vision_factor(TerrainType t){
    if(t==TerrainType::PLAIN)return game.plainTerrainVisionFactor;
    if(t==TerrainType::FOREST)return game.forestTerrainVisionFactor;
    if(t==TerrainType::SWAMP)return game.swampTerrainVisionFactor;
    return 1.0;
  }
  template<class TYPE>
  void init_map(t_map&dest,const vector<vector<TYPE>>&arr){
    for(int y=0;y<dest.h;y++)for(int x=0;x<dest.w;x++)dest.get(x,y)=get_speed_factor(arr[x][y]);
  }
  template<class TYPE>
  void init_map_vis(t_map&dest,const vector<vector<TYPE>>&arr){
    for(int y=0;y<dest.h;y++)for(int x=0;x<dest.w;x++)dest.get(x,y)=get_vision_factor(arr[x][y]);
  }
  void init_maps(){
    if(termap.mem.size())return;
    auto wh=vec2i(1,1)*world.terrainByCellXY.size();
    wetmap.init(wh);
    termap.init(wh);
    init_map(wetmap,world.weatherByCellXY);
    init_map(termap,world.terrainByCellXY);
    vis_wetmap.init(wh);
    vis_termap.init(wh);
    init_map_vis(vis_wetmap,world.weatherByCellXY);
    init_map_vis(vis_termap,world.terrainByCellXY);
    inv_cell_size=real(wetmap.w)/world.width;
  }
  real inv_cell_size;
  //struct t_env:t_app{
  typedef t_app t_env;
  real get_k(const vec2d&pos,bool air){
    return (air?wetmap:termap).get(pos*inv_cell_size);
  }
  real get_vis_k(const vec2d&pos,bool air){
    return (air?vis_wetmap:vis_termap).get(pos*inv_cell_size);
  }
  vec2d get_pos(const Vehicle&v)const{return vec2d(v.x,v.y);}
  vec2d get_pos(const Facility&ref)const{
    static auto wh=vec2d(game.facilityWidth,game.facilityHeight);
    return vec2d(ref.left,ref.top)+wh*0.5;
  }
  vec2d get_obj_size()const{
    static auto wh=vec2d(game.facilityWidth,game.facilityHeight);
    return wh;
  }

  vec2d get_spd(const Vehicle&v){auto*p=id2oldvehs(v.id);return !p?vec2d(0,0):get_pos(v)-get_pos(*p);}
  bool is_moved(const Vehicle&v){
    auto*p=id2oldvehs(v.id);
    if(!p)return false;
    return get_pos(v)!=get_pos(*p);
  }
  int new_group(){return empty_group_id++;}

  //struct t_world:World{
  void update(const World&world)
  {
    init_maps();
    if(id2updated.empty())id2updated.resize(1024*1024);
    if(id2vehid.empty())id2vehid.resize(1024*1024,-1);
    if(id2oldvehid.empty())id2oldvehid.resize(1024*1024,-1);
    if(id2groupid.empty())id2groupid.resize(1024*1024,-1);
    oldvehs=vehs;
    auto dec_till_zero=[](int&v){
      if(!v)return;
      v--;
    };
    QAP_FOREACH(vehs,dec_till_zero(ex.remainingAttackCooldownTicks));
    QAP_FOREACH(oldvehs,id2updated[ex.id]=0);
    QAP_FOREACH(world.newVehicles,qap_add_back(vehs)=ex;id2updated[ex.id]=1;);
    QAP_FOREACH(vehs,id2vehid[ex.id]=i);
    QAP_FOREACH(oldvehs,id2oldvehid[ex.id]=i);
    auto&arr=world.vehicleUpdates;
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      //if(ex.durability==0)continue;
      auto&out=*id2veh(ex.id);
      out=Vehicle(out,ex);
      id2updated[ex.id]=1;
      if(!ex.durability)id2vehid[ex.id]=-1;
    }
    clean_if(vehs,[](const Vehicle&ex){return !ex.durability;});
    QAP_FOREACH(vehs,id2vehid[ex.id]=i);
    QAP_FOREACH(oldvehs,id2oldvehid[ex.id]=i);
    w.load(*this);
  }
  bool is_our(const Vehicle&ref){return ref.playerId==me.id;}
  bool is_our(const Facility&ref){return ref.ownerPlayerId==me.id;}
  template<class TYPE>bool has_type(const TYPE&ref,VehicleType type){return ref.type==type;}
  vec2d GP(const VehicleType&type){
    return getSP(type).getpos();
  }
  vec2d EGP(const VehicleType&type){
    return getSP(type,false).getpos();
  }
  struct t_suppos{
    int n=0;
    vec2d minp;
    vec2d maxp;
    vec2d superpos;
    vec2d superspd;
    real superhp=0;
    int moved=0;
    int updated=0;
    int selected=0;
    vec2d getpos()const{return superpos*(!n?0:1.0/n);}
    vec2d getspd()const{return superspd*(!n?0:1.0/n);}
    vec2d getsize()const{return !n?vec2d(0,0):(maxp-minp).fabs();}
    vec2d getcenter()const{return !n?vec2d(1,1):(maxp+minp)*0.5;}
    real gethp()const{return superhp*(!n?0:1.0/n);}
  };
  t_suppos get_suppos_by_type_impl(const VehicleType&type,bool our=true){
    auto one=vec2d(1,1);
    t_suppos out;out.minp=+one*1e6;out.maxp=-one*1e6;
    QAP_FOREACH(vehs,{
      if(our!=is_our(ex)||(ex.type!=type))return;
      out.n++;
      out.moved+=is_moved(ex);
      out.updated+=id2updated[ex.id];
      out.superpos+=get_pos(ex);
      out.superspd+=get_spd(ex);
      out.superhp+=ex.durability;
      out.selected+=ex.selected;
      vec2d::comax(out.maxp,get_pos(ex));
      vec2d::comin(out.minp,get_pos(ex));
    });
    return out;
  }
  t_suppos get_suppos_by_type(const VehicleType&type,bool our=true){
    static int cur_ticks[2][int(VehicleType::_COUNT_)+1]={{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1}};
    static t_suppos arr[2][int(VehicleType::_COUNT_)+1];
    auto id=int(type)+1;
    auto&ct=cur_ticks[our][id];
    auto&out=arr[our][id];
    if(ct!=world.tickIndex)out=get_suppos_by_type_impl(type,our);
    ct=world.tickIndex;
    return out;
  }
  t_suppos getSP(const VehicleType&type,bool our=true){return get_suppos_by_type(type,our);}

  void act_move(vec2d dir){
    move.action=ActionType::MOVE;
    move.x=dir.x;move.y=dir.y;
  }
  void act_scale(vec2d pos,real factor){
    move.action=ActionType::SCALE;
    move.x=pos.x;move.y=pos.y;move.factor=factor;
  }
  Move&act_select(VehicleType type=VehicleType::_UNKNOWN_)
  {
    move.setAction(ActionType::CLEAR_AND_SELECT);
    move.setRight(world.getWidth());
    move.setBottom(world.getHeight());
    move.vehicleType=type;
    return move;
  }
  void act_add_select(VehicleType type=VehicleType::_UNKNOWN_)
  {
    move.setAction(ActionType::ADD_TO_SELECTION);
    move.setRight(world.getWidth());
    move.setBottom(world.getHeight());
    move.vehicleType=type;
  }
  void act_select_quad(const vec2d&p,const vec2d&half_size,VehicleType type=VehicleType::_UNKNOWN_){
    move.action=ActionType::CLEAR_AND_SELECT;
    auto hs=half_size;
    move.top   =p.y-hs.y;
    move.bottom=p.y+hs.y;
    move.left  =p.x-hs.x;
    move.right =p.x+hs.x;
    move.vehicleType=type;
  }
  void act_assign(int group){move.action=ActionType::ASSIGN;move.group=group;}
  void act_disband(int group){move.action=ActionType::DISBAND;move.group=group;}
  void act_dismiss(int group){move.action=ActionType::DISMISS;move.group=group;}
  void act_rot(vec2d c,real ang=PI){move.setAction(ActionType::ROTATE);move.angle=ang;move.x=c.x;move.y=c.y;}
  //real get_ang_spd_for_center(vec2d c,const Vehicle&ex){
  //  auto d=get_pos(ex).dist_to(c);
  //  return !d?1e9:min_speed(ex.type)/d;
  //}
  //void act_stable_rot(vec2d c,real ang=PI){
  //  //vehs[0].selected
  //  auto id=QAP_MINVAL_ID_OF_VEC(vehs,ex.selected&&is_our(ex)?get_ang_spd_for_center(c,ex):1e9);
  //  if(id<0)return;
  //  //move.setMaxSpeed(0);//get_speed(vehs[id].type));
  //  move.setMaxAngularSpeed(get_ang_spd_for_center(c,vehs[id])*(0.25+0.125*0.25));
  //  move.setAction(ActionType::ROTATE);move.angle=ang;move.x=c.x;move.y=c.y;
  //}
  real get_vis_range(VehicleType t)
  {
    if(t==VT)return game.tankVisionRange;
    if(t==VH)return game.helicopterVisionRange;
    if(t==VA)return game.arrvVisionRange;
    if(t==VI)return game.ifvVisionRange;
    if(t==VF)return game.fighterVisionRange;
    return game.tankVisionRange;
  }
  real get_vision_by_lvl(VehicleType t,int lvl){
    const real wet[]={
      game.clearWeatherVisionFactor,
      game.cloudWeatherVisionFactor,
      game.rainWeatherVisionFactor
    };
    const real ter[]={
      game.plainTerrainVisionFactor,
      game.swampTerrainVisionFactor,//don't copypaste
      game.forestTerrainVisionFactor//see: forest vs swamp
    };
    bool air=t==VH||t==VF;
    return (air?wet:ter)[lvl]*get_vis_range(t);
  }
  real get_speed(VehicleType t){
    if(t==VT)return game.tankSpeed;
    if(t==VH)return game.helicopterSpeed;
    if(t==VA)return game.arrvSpeed;
    if(t==VI)return game.ifvSpeed;
    if(t==VF)return game.fighterSpeed;
    return game.tankSpeed;
  }
  int get_att_cdt(VehicleType t){
    if(t==VT)return game.tankAttackCooldownTicks;
    if(t==VH)return game.helicopterAttackCooldownTicks;
    if(t==VA)return game.tickCount*2;
    if(t==VI)return game.ifvAttackCooldownTicks;
    if(t==VF)return game.fighterAttackCooldownTicks;
    return game.tickCount*2;
  }
  int get_air_dmg(VehicleType t){
    if(t==VT)return game.tankAerialDamage;
    if(t==VH)return game.helicopterAerialDamage;
    if(t==VA)return 0;
    if(t==VI)return game.ifvAerialDamage;
    if(t==VF)return game.fighterAerialDamage;
    return 0;
  }
  int get_gnd_dmg(VehicleType t){
    if(t==VT)return game.tankGroundDamage;
    if(t==VH)return game.helicopterGroundDamage;
    if(t==VA)return 0;
    if(t==VI)return game.ifvGroundDamage;
    if(t==VF)return game.fighterGroundDamage;
    return 0;
  }
  real get_air_range(VehicleType t){
    if(t==VT)return game.tankAerialAttackRange;
    if(t==VH)return game.helicopterAerialAttackRange;
    if(t==VA)return 0;
    if(t==VI)return game.ifvAerialAttackRange;
    if(t==VF)return game.fighterAerialAttackRange;
    return 0;
  }
  real get_gnd_range(VehicleType t){
    if(t==VT)return game.tankGroundAttackRange;
    if(t==VH)return game.helicopterGroundAttackRange;
    if(t==VA)return 0;
    if(t==VI)return game.ifvGroundAttackRange;
    if(t==VF)return game.fighterGroundAttackRange;
    return 0;
  }
  int get_air_def(VehicleType t){
    if(t==VT)return game.tankAerialDefence;
    if(t==VH)return game.helicopterAerialDefence;
    if(t==VA)return game.arrvAerialDefence;
    if(t==VI)return game.ifvAerialDefence;
    if(t==VF)return game.fighterAerialDefence;
    return 0;
  }
  int get_gnd_def(VehicleType t){
    if(t==VT)return game.tankGroundDefence;
    if(t==VH)return game.helicopterGroundDefence;
    if(t==VA)return game.arrvGroundDefence;
    if(t==VI)return game.ifvGroundDefence;
    if(t==VF)return game.fighterGroundDefence;
    return 0;
  }
  real get_max_att_range(){
    static real out=0;
    if(out)return out;
    VehicleType arr[]={VT,VH,VA,VI,VF};
    for(int i=0;i<lenof(arr);i++){
      auto&ex=arr[i];
      out=std::max(out,get_air_range(ex));
      out=std::max(out,get_gnd_range(ex));
    }
    return out;
  }
  static real get_exchange_koef_impl(VehicleType u,VehicleType e){
    auto always_win=0.5;
    if(u==VA)if(e==VA)return 0.0;
    if(u==VF)if(e==VF)return 0.3;
    if(u==VT)if(e==VT)return 0.4;
    if(u==e)return 0.1;

    if(u==VF)if(e==VH)return +1.0;
    if(u==VF)if(e==VT)return 0.0;
    if(u==VF)if(e==VI)return 0.025;//one_dir
    if(u==VF)if(e==VA)return 0.0;
    
    if(u==VH)if(e==VF)return -0.15;
    if(u==VH)if(e==VT)return +0.8;
    if(u==VH)if(e==VI)return +0.075;
    if(u==VH)if(e==VA)return always_win;
    
    if(u==VT)if(e==VF)return 0.0;
    if(u==VT)if(e==VH)return 0.0;
    if(u==VT)if(e==VI)return +0.7;
    if(u==VT)if(e==VA)return always_win;
    
    if(u==VI)if(e==VF)return 0.7;//one_dir
    if(u==VI)if(e==VH)return 0.7;
    if(u==VI)if(e==VT)return 0.0;//one_dir
    if(u==VI)if(e==VA)return always_win;

    return -get_exchange_koef_impl(e,u);
  }
  struct t_exchange_table{
    real table[int(VehicleType::_COUNT_)][int(VehicleType::_COUNT_)];
    real get_koef(VehicleType u,VehicleType e){return table[int(u)][int(e)];}
    static t_exchange_table&get(){
      static t_exchange_table table;
      static bool need_init=true;
      if(!need_init)return table;
      need_init=false;
      int n=int(VehicleType::_COUNT_);
      for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        auto u=VehicleType(i);
        auto e=VehicleType(j);
        table.table[int(u)][int(e)]=get_exchange_koef_impl(u,e);
      }
      return table;
    }
  };
  real min_speed(VehicleType t){
    auto ter=game.swampTerrainSpeedFactor;auto wet=game.rainWeatherSpeedFactor;
    return (t==VH||t==VF?wet:ter)*get_speed(t);
  }
  real mid_speed(VehicleType t){
    auto ter=game.forestTerrainSpeedFactor;auto wet=game.cloudWeatherSpeedFactor;
    return (t==VH||t==VF?wet:ter)*get_speed(t);
  }
  real max_speed(VehicleType t){
    auto ter=game.plainTerrainSpeedFactor;auto wet=game.clearWeatherSpeedFactor;
    return (t==VH||t==VF?wet:ter)*get_speed(t);
  }
  real get_speed_by_lvl(VehicleType t,int lvl){
    const real wet[]={
      game.clearWeatherSpeedFactor,
      game.cloudWeatherSpeedFactor,
      game.rainWeatherSpeedFactor
    };
    const real ter[]={
      game.plainTerrainSpeedFactor,
      game.forestTerrainSpeedFactor,
      game.swampTerrainSpeedFactor
    };
    bool air=t==VH||t==VF;
    return (air?wet:ter)[lvl]*get_speed(t);
  }
  static VehicleType CharToVehicleType(const char type){
    if(type=='H')return VH;
    if(type=='I')return VI;
    if(type=='F')return VF;
    if(type=='T')return VT;
    if(type=='A')return VA;
    QapAssert(false);
    return VehicleType::_UNKNOWN_;
  }
  #ifdef Adler
  static string VehicleTypeToString(VehicleType type){
    if(type==VH)return "VH";
    if(type==VI)return "VI";
    if(type==VF)return "VF";
    if(type==VT)return "VT";
    if(type==VA)return "VA";
    if(type==VehicleType::_UNKNOWN_)return "UNK";
    return "WTF("+IToS(int(type))+")";
  }
  static string ActionToString(ActionType type){
    #define F(X)if(ActionType::X==type)return #X;
    F(_UNKNOWN_);
    F(NONE);
    F(CLEAR_AND_SELECT);
    F(ADD_TO_SELECTION);
    F(DESELECT);
    F(ASSIGN);
    F(DISMISS);
    F(DISBAND);
    F(MOVE);
    F(ROTATE);
    F(SCALE);
    F(SETUP_VEHICLE_PRODUCTION);
    F(TACTICAL_NUCLEAR_STRIKE);
    #undef F
    return "WTF("+IToS(int(type))+")";
  }
  #endif
  bool eq_type(const VehicleType&t,const char type)
  {
    return CharToVehicleType(type)==t;
  }
  bool any_vtype_of(const Vehicle&v,const char*types)
  {
    for(;*types;){if(eq_type(v.type,*types))return true;types++;}return false;
  }
  bool any_vtype_of(const VehicleType&type,const char*types)
  {
    for(;*types;){if(eq_type(type,*types))return true;types++;}return false;
  }

  struct t_cmds{
    struct t_sys_impl{
      static const int counter_base=__COUNTER__+1;
    };
    #define IMPL()/*struct t_sys_impl{*/static const int cmd_id=__COUNTER__-t_cmds::t_sys_impl::counter_base;/*}*/
    struct t_mov{
      vec2d dir;
      real spd=0;
      IMPL();
      Move get()const{Move out;out.action=ActionType::MOVE;out.x=dir.x;out.y=dir.y;out.maxSpeed=spd;return out;}
    };
    struct t_group{
      int group_id=-1;
      bool add=false;
      IMPL();
      Move get()const{QapNoWay();Move out;out.action=add?ActionType::ADD_TO_SELECTION:ActionType::CLEAR_AND_SELECT;out.group=group_id;return out;}
    };
    struct t_rect{
      vec2d pos;
      vec2d size;
      VehicleType type;
      bool add=false;
      IMPL();
      Move get()const{
        Move out;
        out.action=add?ActionType::ADD_TO_SELECTION:ActionType::CLEAR_AND_SELECT;
        auto hs=size*0.5;
        out.left=pos.x-hs.x;out.right=pos.x+hs.x;
        out.top=pos.y-hs.y;out.bottom=pos.y+hs.y;
        out.vehicleType=type;
        return out;
      }
    };
    struct t_rot{
      vec2d pos;
      real ang=0;
      real spd=0;
      IMPL();
      Move get()const{Move out;out.action=ActionType::ROTATE;out.x=pos.x;out.y=pos.y;out.angle=ang;out.maxSpeed=spd;return out;}
    };
    struct t_scale{
      vec2d pos;
      real factor=0;
      real spd=0;
      IMPL();
      Move get()const{Move out;out.action=ActionType::SCALE;out.x=pos.x;out.y=pos.y;out.factor=factor;out.maxSpeed=spd;return out;}
    };
    struct t_bomb{
      vec2d pos;
      int veh_id=-1;
      IMPL();
      Move get()const{Move out;out.action=ActionType::TACTICAL_NUCLEAR_STRIKE;out.x=pos.x;out.y=pos.y;out.vehicleId=veh_id;return out;}
    };
    #undef IMPL
  };

  struct t_move:t_cmds{
    //union{
      t_mov mov;
      t_group group;
      t_rect rect;
      t_rot rot;
      t_scale scale;
      t_bomb bomb;
    //};
    int type=-1;
    //static vector<t_move> get_root_set(){
    //  return get_mov_set();
    //}
    Move get()const{
      #define F(mov)if(type==t_cmds::t_##mov::cmd_id)return mov.get();
      F(mov);
      F(rect);
      F(group);
      F(rot);
      F(scale);
      F(bomb);
      #undef F
      if(type==-1)return Move();
      QapNoWay();
      return Move();
    }
    static vector<vec2d> get_movdirs(real minlen,int len,int dirs){
      /*static */vector<vec2d> id2dir;
      //if(id2dir.size())return id2dir;
      real inv_dirs=1.0/dirs;
      for(int i=0;i<dirs;i++)for(int j=1;j<=len;j++)qap_add_back(id2dir)=Vec2dEx(i*inv_dirs*Pi2,j*minlen);
      return id2dir;
    }
    static vector<vec2d> get_movdirs_norm(int dirs){
      /*static */vector<vec2d> id2dir;
      //if(id2dir.size())return id2dir;
      real inv_dirs=1.0/dirs;
      for(int i=0;i<dirs;i++)qap_add_back(id2dir)=Vec2dEx(i*inv_dirs*Pi2,1.0);
      return id2dir;
    }
    static vector<vec2d> mul(const vector<vec2d>&inp,real k){auto out=inp;QAP_FOREACH(out,ex*=k);return out;}
    //static vector<t_move> get_mov_set(real minlen=1.2*5.0,int len=1,int dirs=8,real maxspd=0,real dspd=0.1){
    //  vector<t_move> out;
    //  auto&arr=get_movdirs(minlen,len,dirs);
    //  for(int i=0;i<arr.size();i++){
    //    auto&ex=arr[i];
    //    for(real spd=0;spd<=maxspd;spd+=dspd){
    //      auto&c=qap_add_back(out);
    //      c.type=c.mov.cmd_id;
    //      auto&m=c.mov;
    //      m.dir=ex;
    //      m.spd=spd;
    //    }
    //  }
    //  return out;
    //}
    //static vector<t_move> get_mov_set_v2(const vector<real>&spds,real minlen=1.2*5.0,int len=1,int dirs=8){
    //  vector<t_move> out;
    //  auto&arr=get_movdirs(minlen,len,dirs);
    //  for(int i=0;i<arr.size();i++){
    //    auto&ex=arr[i];
    //    for(real k=0;k<spds.size();k++){
    //      auto&c=qap_add_back(out);
    //      c.type=c.mov.cmd_id;
    //      auto&m=c.mov;
    //      m.dir=ex;
    //      m.spd=spds[k];
    //    }
    //  }
    //  return out;
    //}  
    static vector<t_move> get_mov_set_v3(t_app&app,VehicleType type,int GAP=5,int len=1,int dirs=8){
      vector<t_move> out;
      auto mdn=get_movdirs_norm(dirs);
      vector<vec2d> arr;
      for(int i=1;i<=len;i++)
      {
        for(int k=0;k<3;k++)
        {
          auto spd_lvl=k;
          auto spd=app.get_speed_by_lvl(type,spd_lvl);
          for(int dir=0;dir<dirs;dir++)
          {
            auto&c=qap_add_back(out);
            c.type=c.mov.cmd_id;
            auto&m=c.mov;
            m.dir=mdn[dir]*spd*len*GAP;
            m.spd=spd;
          }
        }
      }
      return out;
    }
    static vector<t_move> get_mov_set_v4(t_app&app,VehicleType type,int GAP=5,int len=1,int dirs=8){
      vector<t_move> out;
      auto mdn=get_movdirs_norm(dirs);
      vector<vec2d> arr;
      for(int i=1;i<=len;i++)
      {
        auto spd=app.get_speed_by_lvl(type,0);
        for(int dir=0;dir<dirs;dir++)
        {
          auto&c=qap_add_back(out);
          c.type=c.mov.cmd_id;
          auto&m=c.mov;
          m.dir=mdn[dir]*spd*len*GAP;
          m.spd=spd;
        }
      }
      return out;
    }
  };
  //real get_k(const vec2d&pos,bool air){
  //  return 1.0;//(air?wetmap:termap).get(pos*inv_cell_size);
  //}
  //static const real LEN_KOEF=10;

  struct t_building{
    int id=-1;
    int ownerPlayerId;
    FacilityType type;
    VehicleType vehicleType;
    vec2d pos;
    real capturePoints;
    real productionProgress;
    real obj_r;
    void load(t_env&env,const Facility&ref){
      id=ref.id;
      ownerPlayerId=ref.ownerPlayerId;
      type=ref.type;
      vehicleType=ref.vehicleType;
      pos=env.get_pos(ref);
      capturePoints=ref.capturePoints;
      productionProgress=ref.productionProgress;
      obj_r=env.get_obj_size().x*0.5;
    }
    real get_score(const vec2d&p)const{
      auto vdist=(pos-p).fabs();
      auto dist=vdist.max();
      real q=-80.0*25;
      if(dist<obj_r){dist=0;q*=4;}
      return q/(dist*dist+32*32);
    }
  };
  struct t_unit{
    int id=-1;
    int inner_cell_id=-1;
    int hp;
    VehicleType type;
    bool air;
    bool our;
    bool moved=false;//temp
    bool limited=false;
    bool selected=false;
    vec2d prev_pos;
    vec2d pos;
    vec2d next_pos;//temp
    vec2d end;
    real spd;
    real end_maxspd=0;
    real att_cdt=0;
    void move(t_env&env,real LEN_KOEF/*=1*/){
      att_cdt-=LEN_KOEF;
      moved=false;
      prev_pos=pos;next_pos=pos;
      if(end==pos)return;
      auto dir=end-pos;
      auto k=env.get_k(pos,air);
      auto eps=0.3*0.6*0.005;
      limited=bool(spd*k+eps<end_maxspd);
      auto len=limited?spd*k:end_maxspd;
      len*=LEN_KOEF;
      if(len*len>=dir.SqrMag()){next_pos=end;return;}
      next_pos=pos+dir.SetMag(len);
    }
    void use(const t_cmds::t_mov&cmd){
      end=pos+cmd.dir;
      end_maxspd=cmd.spd?cmd.spd:spd;
    }
    void use(const t_cmds::t_group&cmd){QapNoWay();}
    void use(const t_cmds::t_rect&cmd){
      if(cmd.add&&selected)return;
      auto d=(pos-cmd.pos).fabs()*2.0;
      selected=(d.x<cmd.size.x)&&(d.y<cmd.size.y)&&(cmd.type==type||cmd.type==VehicleType::_UNKNOWN_);
    }
    void use(const t_cmds::t_rot&cmd){QapNoWay();}
    void use(const t_cmds::t_scale&cmd){
      end=cmd.pos+(pos-cmd.pos)*cmd.factor;
      end_maxspd=cmd.spd?cmd.spd:spd;
    }
    void load(t_env&env,const Vehicle&v){
      pos=env.get_pos(v);prev_pos=pos;end=pos;
      air=v.aerial;
      spd=env.get_speed(v.type);end_maxspd=0;
      id=v.id;
      our=env.is_our(v);
      hp=v.durability;
      type=v.type;
      att_cdt=v.remainingAttackCooldownTicks;
    }
  };
  bool is_our(const t_unit&ref)const{return ref.our;}
  vec2d get_pos(const t_unit&ref)const{return ref.pos;}
  struct t_nuclear_explosion{
    vec2d pos;
    int host_id=-1;
    real ticks=20*10000*64;
    real rcd=0;
    void load(const Player&ref,int tickIndex){
      ticks=ref.nextNuclearStrikeTickIndex-tickIndex;
      host_id=ref.nextNuclearStrikeVehicleId;
      pos=vec2d(ref.nextNuclearStrikeX,ref.nextNuclearStrikeY);
      rcd=ref.remainingNuclearStrikeCooldownTicks;
    }
    operator bool(){return host_id>=0;}
  };
  struct t_world{
    vector<t_unit> etops;
    vector<t_unit> elows;
    vector<t_unit> tops;
    vector<t_unit> lows;
    real r=-1;
    real w=-1;
    real h=-1;
    real ofv_factory_score=0;
    real ofv_control_score=0;
    real ofv_factory_product=0;
    real ofv_control_product=0;
    int nuke_delay=30;
    int tickIndex=0;
    int cdn=0;
    int limiteds=0;
    int mescore=0;
    int opscore=0;
    t_nuclear_explosion nuke_a;
    t_nuclear_explosion nuke_b;
    vector<t_building> objs;
    #define FOREACH_UNIT(CODE)QAP_FOREACH(etops,CODE);QAP_FOREACH(elows,CODE);QAP_FOREACH(tops,CODE);QAP_FOREACH(lows,CODE);
    struct t_suppos{
      int air=0;
      int n=0;
      vec2d minp;
      vec2d maxp;
      vec2d superpos;
      real superhp=0;
      vec2d getpos()const{return superpos*(!n?0:1.0/n);}
      vec2d getsize()const{return (maxp-minp).fabs();}
      real gethp()const{return superhp*(!n?0:1.0/n);}
    };
    t_suppos getSP(bool our=true){return get_sel_suppos_impl(our);}
    t_suppos get_sel_suppos_impl(bool our=true){
      auto one=vec2d(1,1);
      t_suppos out;out.minp=+one*1e6;out.maxp=-one*1e6;
      FOREACH_UNIT({
        if(our!=ex.our||!ex.selected)return;
        out.n++;
        if(ex.air)out.air++;
        out.superpos+=ex.pos;
        out.superhp+=ex.hp;
        vec2d::comax(out.maxp,ex.pos);
        vec2d::comin(out.minp,ex.pos);
      });
      return out;
    }
    struct t_arr{
      t_world&w;
      t_unit&operator[](int id){
        {auto&arr=w.etops;auto n=arr.size();if(id<n){return arr[id];}id-=n;}
        {auto&arr=w.elows;auto n=arr.size();if(id<n){return arr[id];}id-=n;}
        {auto&arr=w.tops;auto n=arr.size();if(id<n){return arr[id];}id-=n;}
        {auto&arr=w.lows;auto n=arr.size();if(id<n){return arr[id];}id-=n;}
        QapNoWay();static t_unit tmp;return tmp;
      }
      size_t size()const{return w.etops.size()+w.elows.size()+w.tops.size()+w.lows.size();}
      template<class FUNC>
      void for_each(FUNC func,int offset=0){
        int tn=0;
        for(int i=std::max<int>(offset-tn,0);i<w.etops.size();i++)func(w.etops[i],i+00);tn+=w.etops.size();
        for(int i=std::max<int>(offset-tn,0);i<w.elows.size();i++)func(w.elows[i],i+tn);tn+=w.elows.size();
        for(int i=std::max<int>(offset-tn,0);i<w. tops.size();i++)func(w. tops[i],i+00);tn+=w. tops.size();
        for(int i=std::max<int>(offset-tn,0);i<w. lows.size();i++)func(w. lows[i],i+tn);tn+=w. lows.size();
      }
      bool empty()const{return 0==w.etops.size()+w.elows.size()+w.tops.size()+w.lows.size();}
    };
    t_arr get_arr(){return {*this};}
    void step(t_env&env,real LEN_KOEF){FOREACH_UNIT(ex.move(env,LEN_KOEF));}
    void sel_clear(){
      FOREACH_UNIT(ex.selected=false);
    }
    void sel_by_type(VehicleType type,bool add=false){
      //FOREACH_UNIT(if(ex.selected)QapAssert(ex.our));
      if(add){FOREACH_UNIT(ex.selected=ex.selected||(ex.type==type&&ex.our));return;}
      FOREACH_UNIT(ex.selected=(ex.type==type&&ex.our));
    }
    vector<int> get_sel_ids(bool our){
      vector<int> out;
      FOREACH_UNIT(if(ex.our!=our)return;if(ex.selected)qap_add_back(out)=ex.id;);
      return out;
    }
    void sel_all(bool our){
      FOREACH_UNIT(ex.selected=our==ex.our);
    }
    int sel_count(bool our){int n=0;FOREACH_UNIT(if(ex.selected&&ex.our==our)n++;);return n;}
    static real get_range(t_env&env,const t_unit&from,const t_unit&to){
      return to.air?env.get_air_range(from.type):env.get_gnd_range(from.type);
    }
    static real get_dmg(t_env&env,const t_unit&from,const t_unit&to){
      return to.air?env.get_air_dmg(from.type):env.get_gnd_dmg(from.type);
    }
    static real get_def(t_env&env,const t_unit&attacker,const t_unit&receiver){
      return attacker.air?env.get_air_def(receiver.type):env.get_gnd_def(receiver.type);
    }
    static void dmg_exchange_impl(t_env&env,t_unit&a,t_unit&b,real sqr_dist)
    {
      auto ar=get_range(env,a,b);
      if(sqr_dist>ar*ar)return;
      auto dhp=get_dmg(env,a,b)-get_def(env,a,b);
      if(dhp<=0)return;
      b.hp-=dhp;
      a.att_cdt=env.get_att_cdt(a.type);
    }
    static void dmg_exchange(t_env&env,t_unit&a,t_unit&b,real sqr_dist)
    {
      auto eps=0.001;
      if(a.att_cdt<eps)dmg_exchange_impl(env,a,b,sqr_dist);
      if(b.att_cdt<eps)dmg_exchange_impl(env,b,a,sqr_dist);
    }
    struct t_team_arr{
      vector<t_unit>&tops;
      vector<t_unit>&lows;
      //t_unit&operator[](int id){
      //  {auto&arr=tops;auto n=arr.size();if(id<n){return arr[id];}id-=n;}
      //  {auto&arr=lows;auto n=arr.size();if(id<n){return arr[id];}id-=n;}
      //  QapNoWay();static t_unit tmp;return tmp;
      //}
      //size_t size()const{return tops.size()+lows.size();}
      template<class FUNC>
      void for_each(FUNC func,int offset=0){
        int tn=tops.size();
        for(int i=offset;i<tops.size();i++)func(tops[i],i);
        for(int i=std::max<int>(offset-tn,0);i<lows.size();i++)func(lows[i],i+tn);
      }
      bool empty()const{return 0==tops.size()+lows.size();}
    };
    t_team_arr get_team_arr(bool our){return our?t_team_arr{tops,lows}:t_team_arr{etops,elows};}
    void attack_v1(t_env&env)
    {
      auto eps=0.001;static auto max_att_range=env.get_max_att_range()+eps;
      auto A=get_team_arr(true);
      auto B=get_team_arr(false);
      auto func=[&](t_unit&a,int i)
      {
        auto f=[&](t_unit&b)
        {
          if(fabs(a.pos.x-b.pos.x)>max_att_range)return;
          if(fabs(a.pos.y-b.pos.y)>max_att_range)return;
          if(b.hp<=0)return;
          if(a.att_cdt>eps&&b.att_cdt>eps)return;
          if(a.type==VA&&b.type==VA)return;
          auto sqr_dist=a.pos.sqr_dist_to(b.pos);
          dmg_exchange(env,a,b,sqr_dist);
        };
        for(int j=0;j<B.tops.size();j++){
          if(a.hp<0)break;
          f(B.tops[j]);
        }
        for(int j=0;j<B.lows.size();j++){
          if(a.hp<0)break;
          f(B.lows[j]);
        }
      };
      A.for_each(func);
      clean_if(etops,[](const t_unit&ex){return ex.hp<=0;});
      clean_if(elows,[](const t_unit&ex){return ex.hp<=0;});
      clean_if(tops,[](const t_unit&ex){return ex.hp<=0;});
      clean_if(lows,[](const t_unit&ex){return ex.hp<=0;});
    }
    struct t_att_cell{
      static const int MAX_N=64*4;
      int n=0;
      t_unit*arr[MAX_N];
      void set_to_def(){n=0;}
      int add(t_unit*p){QapAssert(n+1<MAX_N);arr[n]=p;n++;return n-1;}
    };
    struct t_att_env{
      t_map_v2<t_att_cell> map;
      real inv_cell_size;
      void init(vec2i wh){
        if(map.mem.empty()){
          map.init(wh);
        }else{
          QAP_FOREACH(map.mem,ex.n=0);
        }
      }
      void put(t_unit&ex){
        auto&c=map.get(ex.pos*inv_cell_size);
        c.add(&ex);
      }
      template<class FUNC>
      void attack_for(t_unit&u,FUNC func){
        vec2d real_base=u.pos*inv_cell_size;
        vec2i base=vec2i(real_base.x,real_base.y);
        for(int y=-1;y<=+1;y++)for(int x=-1;x<=+1;x++){
          auto&c=map.get(base+vec2i(x,y));
          for(int i=0;i<c.n;i++){
            auto&ex=*c.arr[i];
            func(ex);
          }
        }
      }
      template<class FUNC>
      void foreach_from_nightbours(const vec2d&pos,int d,FUNC func)
      {
        vec2d real_base=pos*inv_cell_size;
        vec2i base=vec2i(real_base.x,real_base.y);
        for(int y=-d;y<=+d;y++)for(int x=-d;x<=+d;x++)
        {
          auto&c=map.get(base+vec2i(x,y));
          for(int i=0;i<c.n;i++){
            auto&ex=*c.arr[i];
            func(ex);
          }
        }
      }
      template<class FUNC>
      void foreach_from_nightbours_v2(const vec2d&pos,FUNC func)
      {
        vec2d real_base=(pos-vec2d(1,1))*inv_cell_size;
        vec2i base=vec2i(real_base.x,real_base.y);
        for(int y=0;y<=1;y++)for(int x=0;x<=1;x++)
        {
          auto&c=map.get(base+vec2i(x,y));
          for(int i=0;i<c.n;i++){
            auto&ex=*c.arr[i];
            func(ex);
          }
        }
      }
    };
    void attack(t_env&env){
      attack_v2(env);
    }
    void attack_v2(t_env&env)
    {
      if(get_team_arr(false).empty())return;
      auto eps=0.001;static auto max_att_range=env.get_max_att_range()+eps;
      auto A=get_team_arr(true);
      int size=32;auto d=max_att_range*2;auto dd=d*d;
      static t_att_env ae;
      ae.inv_cell_size=real(size)/w;
      ae.init(vec2i(1,1)*size);
      FOREACH_UNIT(if(!ex.our)ae.put(ex));
      auto func=[&](t_unit&a,int i)
      {
        auto f=[&](t_unit&b)
        {
          if(fabs(a.pos.x-b.pos.x)>max_att_range)return;
          //if(fabs(a.pos.y-b.pos.y)>max_att_range)return;
          if(b.hp<=0||a.hp<=0)return;
          if(a.att_cdt>eps&&b.att_cdt>eps)return;
          if(a.type==VA&&b.type==VA)return;
          auto sqr_dist=a.pos.sqr_dist_to(b.pos);
          dmg_exchange(env,a,b,sqr_dist);
        };
        ae.attack_for(a,f);
      };
      A.for_each(func);
      clean_if(etops,[](const t_unit&ex){return ex.hp<=0;});
      clean_if(elows,[](const t_unit&ex){return ex.hp<=0;});
      clean_if(tops,[](const t_unit&ex){return ex.hp<=0;});
      clean_if(lows,[](const t_unit&ex){return ex.hp<=0;});
      #ifdef Adler
      FOREACH_UNIT(if(!ex.our)ex.inner_cell_id=-1);
      #endif
    }
    bool has_cd_quad(const t_unit&a){return cd_quad(a);}
    bool has_cd_for(vector<t_unit>&arr,int id)
    {
      auto&a=arr[id];
      //if(cd_quad(a))return true;
      for(int i=0;i<arr.size();i++)if(id!=i)
      {
        auto&b=arr[i];
        if(b.id==a.id)continue;
        if(a.air&&a.our!=b.our)continue;
        if(!cd(a.next_pos,b.pos))continue;
        int gg=1;
        return true;
      }
      return false;
    }
    
    bool has_cd_for_v2(vector<t_unit>&arr,const t_unit&eunit)
    {
      auto&a=eunit;auto d=r+r;auto dd=d*d;
      //if(cd_quad(a))return true;
      for(int i=0;i<arr.size();i++)
      {
        auto&b=arr[i];
        //if(b.id==a.id)continue;
        //if(a.air&&a.our!=b.our)continue;
        if(fabs(a.next_pos.x-b.pos.x)>=d)continue;
        if(a.next_pos.sqr_dist_to(b.pos)>=dd)continue;
        //if(!cd(a.next_pos,b.pos))continue;
        int gg=1;
        return true;
      }
      return false;
    }
    void cd_update()
    {
      QAP_PERF("cd_update");
      NO_QAP_PERF_CODE(cd_rounds_for(etops););
      NO_QAP_PERF_CODE(cd_rounds_for(tops););
      QAP_PERF_CODE(cd_rounds_for_v2(elows,lows););

      NO_QAP_PERF_CODE(FOREACH_UNIT(if(!ex.moved&&ex.our)cdn++););
      NO_QAP_PERF_CODE(FOREACH_UNIT(if(ex.limited&&ex.our)limiteds++););
    }
    struct t_cell{
      static const int GRID_SIZE=64*4;
      static const int MAX_N=4+2;
      int call_id=-1;
      int n=0;
      t_unit*arr[MAX_N];
      void set_to_def(){n=0;call_id=-1;}
      int add(t_unit*p){QapAssert(n+1<MAX_N);arr[n]=p;n++;return n-1;}
    };
    struct t_cd_env{
      real d,dd;
      int call_id;
      t_map_v2<t_cell> map;
      real inv_cell_size;
      void init(vec2i wh){
        if(map.mem.empty()){
          map.init(wh);
          call_id=-1;
        }else{
          //QAP_FOREACH(map.mem,ex.n=0);
        }
        call_id++;
      }
      static vec2i to_vec2i(const vec2d&v){return vec2i(v.x,v.y);}
      void del_move_put(t_unit&ex)
      {
        auto c_prev=to_vec2i(ex.pos*inv_cell_size);
        auto c_next=to_vec2i(ex.next_pos*inv_cell_size);
        if(c_prev==c_next){
          ex.pos=ex.next_pos;
          return;
        }
        del(ex);
        ex.pos=ex.next_pos;
        put(ex);
      }
      void put(t_unit&ex){
        auto&c=map.get(ex.pos*inv_cell_size);
        #ifdef Adler
        QapAssert(ex.inner_cell_id==-1);
        #endif
        if(c.call_id!=call_id)
        {
          c.call_id=call_id;
          c.n=0;
        }
        ex.inner_cell_id=c.add(&ex);
      }
      void del(t_unit&ex){
        auto&c=map.get(ex.pos*inv_cell_size);
        #ifdef Adler
        QapAssert(c.call_id==call_id);
        QapAssert(ex.inner_cell_id>=0);
        QapAssert(ex.inner_cell_id<c.n);
        #endif
        c.arr[ex.inner_cell_id]=nullptr;
        #ifdef Adler
        ex.inner_cell_id=-1;
        #endif
      }
      bool has_cd_for(t_unit&u)
      {
        vec2d real_base=u.next_pos*inv_cell_size;
        vec2i base=vec2i(real_base.x,real_base.y);
        for(int y=-1;y<=+1;y++)for(int x=-1;x<=+1;x++)
        {
          auto&c=map.get(base+vec2i(x,y));
          if(c.call_id!=call_id)continue;
          for(int i=0;i<c.n;i++)
          {
            auto*p=c.arr[i];
            if(!p||p==&u)continue;
            if(p->pos.sqr_dist_to(u.next_pos)<dd)return true;
          }
        }
        return false;
      }
      int count_nightbours(const vec2i&base,bool our,int d=1)
      {
        int n=0;
        for(int y=-d;y<=+d;y++)for(int x=-d;x<=+d;x++)
        {
          auto&c=map.get(base+vec2i(x,y));
          if(c.call_id!=call_id)continue;
          for(int i=0;i<c.n;i++)
          {
            auto*p=c.arr[i];
            if(!p)continue;
            if(p->our!=our)continue;
            n++;
          }
        }
        return n;
      }
    };
    void cd_rounds_for_v2x2(vector<t_unit>&earr,vector<t_unit>&arr){
      int size=t_cell::GRID_SIZE;auto d=r+r;auto dd=d*d;
      static t_cd_env ce={d,dd};
      ce.inv_cell_size=real(size)/w;
      ce.init(vec2i(1,1)*size);
      QAP_FOREACH(earr,ce.put(ex);ex.moved=ex.next_pos==ex.pos);
      QAP_FOREACH(arr,ce.put(ex);ex.moved=ex.next_pos==ex.pos);
      for(;;)
      {
        int n=0;
        auto f=[&](t_unit&ex)
        {
          if(ex.moved)return;
          QapAssert(ex.next_pos!=ex.pos);
          bool fail=has_cd_quad(ex);
          if(fail)return;
          fail=ce.has_cd_for(ex);
          if(fail)return;
          ex.moved=true;
          ce.del_move_put(ex);
          n++;
        };
        QAP_FOREACH(earr,f(ex));
        QAP_FOREACH(arr,f(ex));
        if(!n)break;
      }
      #ifdef Adler
      QAP_FOREACH(earr,ex.inner_cell_id=-1);
      QAP_FOREACH(arr,ex.inner_cell_id=-1);
      #endif
    }
    int cd_rounds_for_v2_one_dir(vector<t_unit>&earr,vector<t_unit>&arr)
    {
      int n=0;
      for(int i=0;i<earr.size();i++)
      {
        auto&ex=earr[i];
        if(ex.moved)continue;
        if(ex.next_pos==ex.pos){ex.moved=true;ex.pos=ex.next_pos;continue;}
        bool fail=has_cd_quad(ex)||has_cd_for(earr,i)||has_cd_for_v2(arr,ex);
        if(fail)continue;
        ex.moved=true;
        ex.pos=ex.next_pos;
        n++;
      }
      return n;
    }
    void cd_rounds_for_v2x0(vector<t_unit>&earr,vector<t_unit>&arr)
    {
      for(;;)
      {
        int n=0;
        n+=cd_rounds_for_v2_one_dir(earr,arr);
        n+=cd_rounds_for_v2_one_dir(arr,earr);
        if(!n)return;
      }
    }
    void cd_rounds_for_v2(vector<t_unit>&earr,vector<t_unit>&arr)
    {
      cd_rounds_for_v2x2(earr,arr); //21 ms/frame at 3k frame
      return;
      /*
      //static vector<t_mv> moved;auto&b=qap_add_back(moved);
      //QAP_FOREACH(earr,if(ex.moved)qap_add_back(b.OP)=i);
      // QAP_FOREACH(arr,if(ex.moved)qap_add_back(b.ME)=i);
      //if(tickIndex==320){
      //  int gg=10;
      //  QapSaveToFile("moved.bin",moved);
      //  //exit(0);
      //}
      //int gg=1;return;
      vector<t_mv>*v2;
      {
        static vector<t_mv> A;v2=&A;
        if(A.empty())QapLoadFromFile("moved.bin",A);
        static int callid=-1;callid++;
        auto&rec=A[callid];
        
        //QAP_FOREACH(rec.OP,QapAssert(earr[ex].moved));
        //QAP_FOREACH(rec.ME,QapAssert(arr[ex].moved));
        //QAP_FOREACH(earr,if(!ex.moved)return;QapAssert(ex.pos==ex.next_pos));
        //QAP_FOREACH( arr,if(!ex.moved)return;QapAssert(ex.pos==ex.next_pos));
        
        QAP_FOREACH(rec.OP,earr[ex].moved=true);
        QAP_FOREACH(rec.ME,arr[ex].moved=true);
        QAP_FOREACH(earr,if(!ex.moved)return;ex.pos=ex.next_pos);
        QAP_FOREACH( arr,if(!ex.moved)return;ex.pos=ex.next_pos);
      }
      //QapAssert((*v2)[moved.size()-1]==moved.back());
      */
    }
    #ifdef Adler
    struct t_mv{
      #define DEF_PRO_CLASSNAME()t_mv
      #define DEF_PRO_VARIABLE(ADD)\
      ADD(vector<int>,OP,$)\
      ADD(vector<int>,ME,$)\
      //===
      #include "qaplite/defprovar.inl"
      //===
    };
    #endif
    void cd_rounds_for(vector<t_unit>&arr){
      if(arr.size()>50)return cd_rounds_for_v1x2(arr);
      cd_rounds_for_v1x0(arr);
    }
    void cd_rounds_for_v1x0(vector<t_unit>&arr)
    {
      for(;;)
      {
        int n=0;
        for(int i=0;i<arr.size();i++)
        {
          auto&ex=arr[i];
          if(ex.moved)continue;
          if(ex.next_pos==ex.pos){ex.moved=true;ex.pos=ex.next_pos;continue;}
          if(has_cd_quad(ex))continue;
          bool fail=has_cd_for(arr,i);
          if(fail)continue;
          ex.moved=true;
          ex.pos=ex.next_pos;
          n++;
        }
        if(!n)return;
      }
    }
    void cd_rounds_for_v1x2(vector<t_unit>&arr)
    {
      int size=t_cell::GRID_SIZE;auto d=r+r;auto dd=d*d;
      static t_cd_env ce={d,dd};
      ce.inv_cell_size=real(size)/w;
      ce.init(vec2i(1,1)*size);
      QAP_FOREACH(arr,ce.put(ex);ex.moved=ex.next_pos==ex.pos);
      for(;;)
      {
        int n=0;
        auto f=[&](t_unit&ex)
        {
          if(ex.moved)return;
          QapAssert(ex.next_pos!=ex.pos);
          bool fail=has_cd_quad(ex);
          if(fail)return;
          fail=ce.has_cd_for(ex);
          if(fail)return;
          ex.moved=true;
          ce.del_move_put(ex);
          n++;
        };
        QAP_FOREACH(arr,f(ex));
        if(!n)break;
      }
      #ifdef Adler
      QAP_FOREACH(arr,ex.inner_cell_id=-1);
      #endif
    }
    bool cd_quad(const t_unit&ex){return cd_quad(ex.next_pos);}
    bool cd_quad(const vec2d&p){return !((p.x>r&&p.x<-r+w)&&(p.y>r&&p.y<-r+h));}
    bool cd(const vec2d&a,const vec2d&b){return a.dist_to_point_less_that_r(b,r+r);}
    #define LIST(USE)\
      USE(mov,ex.selected);\
      USE(group,ex.hp>0);\
      USE(rect,ex.hp>0);\
      USE(rot,ex.selected);\
      USE(scale,ex.selected);\
      //
    #define USE(CMD,COND)void use(const t_cmds::t_##CMD&cmd,bool our){FOREACH_UNIT(if(ex.our==our)if(COND)ex.use(cmd));}
    LIST(USE)
    #undef USE
    void use(const t_move&cmd,bool our){
      #define USE(CMD,COND)if(cmd.type==t_cmds::t_##CMD::cmd_id)return use(cmd.CMD,our);
      LIST(USE)
      #undef LIST
      if(cmd.type==t_cmds::t_bomb::cmd_id)return use(cmd.bomb,our);
      if(cmd.type<0)return;
      QapNoWay();
    }
    #undef LIST
    void use(const t_cmds::t_bomb&cmd,bool our){
      auto&n=our?nuke_a:nuke_b;
      n.host_id=cmd.veh_id;
      n.pos=cmd.pos;
      n.ticks=nuke_delay;
    }
    void apply_cap(real cap,real new_cap,real dc,bool factory)
    {
      auto&v=factory?ofv_factory_score:ofv_control_score;
      v+=dc;
    }
    void update_objs(t_env&env,real LEN_KOEF)
    {
      if(objs.empty())return;
      QAP_PERF("update_objs");
      static const auto obj_half_size=env.get_obj_size().x*0.5;
      static const auto max_cap=env.game.maxFacilityCapturePoints;
      static const auto cap_spd=env.game.facilityCapturePointsPerVehiclePerTick;
      const auto&op=env.op.id;
      const auto&me=env.me.id;
      // we can't reuse ae from attack_v2 because only air units can capture objs
      int size=32;
      static t_att_env ae;
      ae.inv_cell_size=real(size)/w;
      ae.init(vec2i(1,1)*size);
      QAP_FOREACH(elows,ae.put(ex));
      QAP_FOREACH(lows,ae.put(ex));
      for(int i=0;i<objs.size();i++)
      {
        auto&obj=objs[i];
        auto&ooid=obj.ownerPlayerId;
        auto&cap=obj.capturePoints;
        real dc=0.0;
        auto f=[&](t_unit&u){
          auto dist=(u.pos-obj.pos).fabs().max();
          if(dist>obj_half_size)return;
          dc+=(u.our?+1:-1)*cap_spd*LEN_KOEF;
        };
        ae.foreach_from_nightbours_v2(obj.pos,f);
        //QAP_FOREACH(elows,f(ex));
        //QAP_FOREACH(lows,f(ex));
        auto new_cap=cap+dc;
        int product=0;
        if(new_cap>=+max_cap){dc=+max_cap-cap;product++;if(me!=ooid){ooid=me;mescore+=env.game.facilityCaptureScore;}}
        if(new_cap<=-max_cap){dc=-max_cap-cap;product--;if(op!=ooid){ooid=op;opscore+=env.game.facilityCaptureScore;}}
        new_cap=cap+dc;
        if(op==ooid)if(new_cap>0)ooid=-1;
        if(me==ooid)if(new_cap<0)ooid=-1;
        bool factory=obj.type==FacilityType::VEHICLE_FACTORY;
        apply_cap(cap,new_cap,dc,factory);
        cap=new_cap;
        if(product>0)
        {
          auto&v=factory?ofv_factory_product:ofv_control_product;
          v+=product;
        }
      }
      //
      #ifdef Adler
      QAP_FOREACH(elows,ex.inner_cell_id=-1);
      QAP_FOREACH(lows,ex.inner_cell_id=-1);
      #endif
    }
    void update(t_env&env,real LEN_KOEF=1,bool sim_attack=true){
      QAP_PERF_CODE(step(env,LEN_KOEF));
      cd_update();
      nuke_update(env,nuke_a,LEN_KOEF);
      nuke_update(env,nuke_b,LEN_KOEF);
      if(sim_attack)QAP_PERF_CODE(attack(env));
      update_objs(env,LEN_KOEF);
      tickIndex++;
    }
    t_unit*get_phost(int host_id){
      t_unit*phost=nullptr;FOREACH_UNIT(if(ex.id==host_id)phost=&ex);
      return phost;
    }
    void nuke_update(t_env&env,t_nuclear_explosion&nuke,real LEN_KOEF=1)
    {
      nuke_update_impl(env,nuke,LEN_KOEF);
      if(nuke.host_id>=0)nuke.ticks-=LEN_KOEF;
      nuke.rcd-=LEN_KOEF;
    }
    void nuke_update_impl(t_env&env,t_nuclear_explosion&nuke,real LEN_KOEF=1)
    {
      if(nuke.host_id<0)return;
      t_unit*phost=nullptr;FOREACH_UNIT(if(ex.id==nuke.host_id)phost=&ex);
      auto nr=env.game.tacticalNuclearStrikeRadius;
      if(!phost){nuke.host_id=-1;return;}
      auto&h=*phost;
      auto vision_range=env.get_vis_k(h.pos,h.air)*env.get_vis_range(h.type);
      if(!h.pos.dist_to_point_less_that_r(nuke.pos,vision_range)){nuke.host_id=-1;return;}
      if(nuke.ticks>0.001)return;
      nuke.host_id=-1;
      auto nmaxdmg=env.game.maxTacticalNuclearStrikeDamage;
      auto nmaxdmg_div_nr=nmaxdmg/nr;;
      FOREACH_UNIT(
        auto dd=ex.pos.sqr_dist_to(nuke.pos);
        if(dd>=nr*nr)return;
        auto d=sqrt(dd);
        ex.hp=std::max<real>(0,ex.hp-nmaxdmg_div_nr*(nr-d));
      );
    }
    vector<t_unit>&get_subarr(bool air,bool our){
      if(our)return air?tops:lows;
      return air?etops:elows;
    }
    void load(t_env&env,bool force=false)
    {
      tickIndex=env.world.tickIndex;
      if(!env.world.tickIndex||force){
        w=env.game.worldWidth;h=env.game.worldHeight;r=env.game.vehicleRadius;nuke_delay=env.game.tacticalNuclearStrikeDelay;
        QapAssert(!tops.size());
        QAP_FOREACH(env.vehs,qap_add_back(get_subarr(ex.aerial,env.is_our(ex))).load(env,ex));
        QAP_FOREACH(env.objs,qap_add_back(objs).load(env,ex));objs.shrink_to_fit();
        fprintf(stderr,"on world load\n");
        //split();
        int gg=1;
      }else
      {
        mescore=env.me.score;opscore=env.op.score;
        QAP_FOREACH(objs,if(auto*p=env.id2obj(ex.id))ex.load(env,*p));
        auto upd=[&](t_unit&ex){
          auto*p=env.id2veh(ex.id);
          if(!p||!p->durability){ex.hp=0;return;}
          ex.hp=p->durability;
          ex.pos=env.get_pos(*p);
          ex.att_cdt=p->remainingAttackCooldownTicks;
          ex.selected=p->selected;
          if(!ex.our)ex.end=ex.pos+env.get_spd(*p);
        };
        FOREACH_UNIT(upd(ex));
        //env.world.newVehicles[0].id
        QAP_FOREACH(env.world.newVehicles,qap_add_back(get_subarr(ex.aerial,env.is_our(ex))).load(env,ex));
        {
          nuke_b.load(env.op,env.world.tickIndex);
          nuke_a.load(env.me,env.world.tickIndex);
        }
        clean_if(etops,[](const t_unit&ex){return ex.hp<=0;});
        clean_if(elows,[](const t_unit&ex){return ex.hp<=0;});
        clean_if(tops,[](const t_unit&ex){return ex.hp<=0;});
        clean_if(lows,[](const t_unit&ex){return ex.hp<=0;});
      }
    }
    void shrink_to_fit(){etops.shrink_to_fit();elows.shrink_to_fit();tops.shrink_to_fit();lows.shrink_to_fit();}
    void set_enemy_end_pos(int GAP){
      FOREACH_UNIT(if(ex.our)return;auto spd=(ex.end-ex.pos);ex.end=ex.pos+spd*GAP;ex.end_maxspd=spd.Mag(););
    }
    real get_cur_hp(bool our){
      real hp=0;
      FOREACH_UNIT(if(our!=ex.our)return;hp+=ex.hp>0?ex.hp:0);
      return hp;
    }
    real get_cur_team_power(bool our,real bonus_per_frag=15){
      real power=0;
      FOREACH_UNIT(if(our!=ex.our)return;power+=ex.hp>0?ex.hp*unit_hp_cost(ex.type)+bonus_per_frag*unit_frag_cost(ex.type):0);
      return power;
    }
    real get_cur_power_diff(real koef=1.0){
      return get_cur_team_power(false)-get_cur_team_power(true)*koef;
    }
    real get_score_diff(real koef=1.0){
      return opscore-mescore*koef;
    }
    inline static real unit_hp_cost(const VehicleType type){
      if(type==VA)return 0.3;
      if(type==VH)return 1.25;
      return 1.0;
    }
    inline static real unit_frag_cost(const VehicleType type){return 1.0;}
    real get_expected_nuclear_dmg(t_env&env,vec2d pos,bool our,real bonus_per_frag=10){
      static const auto sel_and_mov_time=1+1;
      static const auto delay=std::max<int>(0,env.game.tacticalNuclearStrikeDelay-sel_and_mov_time);//
      auto nr=env.game.tacticalNuclearStrikeRadius;
      auto nmaxdmg=env.game.maxTacticalNuclearStrikeDamage;
      auto nmaxdmg_div_nr=nmaxdmg/nr;;
      real dmg=0;
      FOREACH_UNIT(
        if(our!=ex.our)return;
        auto dd=ex.pos.sqr_dist_to(pos);
        if(dd>=nr*nr)return;
        auto d=sqrt(dd);
        auto cur_spd=ex.spd*env.get_k(ex.pos,ex.air);
        auto dr=cur_spd*delay;
        if(d+dr>=nr)return;
        auto ex_hp=std::max<real>(0,ex.hp-nmaxdmg_div_nr*(nr-(d+dr)));
        dmg+=fabs(ex_hp-ex.hp)*unit_hp_cost(ex.type);
        if(ex_hp<=0)dmg+=bonus_per_frag*unit_frag_cost(ex.type);
      );
      return dmg;
    }
    real get_nuclear_dmg(t_env&env,vec2d pos,bool our,real bonus_per_frag=10){
      auto nr=env.game.tacticalNuclearStrikeRadius;
      auto nmaxdmg=env.game.maxTacticalNuclearStrikeDamage;
      auto nmaxdmg_div_nr=nmaxdmg/nr;;
      real dmg=0;
      FOREACH_UNIT(
        if(our!=ex.our)return;
        auto dd=ex.pos.sqr_dist_to(pos);
        if(dd>=nr*nr)return;
        auto d=sqrt(dd);
        auto ex_hp=std::max<real>(0,ex.hp-nmaxdmg_div_nr*(nr-d));
        dmg+=fabs(ex_hp-ex.hp)*unit_hp_cost(ex.type);
        if(ex_hp<=0)dmg+=bonus_per_frag*unit_frag_cost(ex.type);
      );
      return dmg;
    }
    real get_nuclear_dmg_diff(t_env&env,vec2d pos){
      return get_nuclear_dmg(env,pos,true)-get_nuclear_dmg(env,pos,false);//less = better
    }
    VehicleType get_sel_slowest_type(t_env&env,bool our){
      static vector<t_unit*> tmp;tmp.clear();
      FOREACH_UNIT(if(ex.our!=our||!ex.selected)return;qap_add_back(tmp)=&ex);
      auto id=QAP_MINVAL_ID_OF_VEC(tmp,env.get_speed_by_lvl(ex->type,2));
      if(id<0)return VT;
      return tmp[id]->type;
    }
  };
  t_world w,sim_w;t_move sim_move;Player op;
  vector<string> info;
  struct t_world_log{
    t_move sim_move;
    t_world w;
    t_world sim_w;
    Player me;
    Player op;
    //vector<Vehicle> vehs;
    vector<Facility> objs;
    vector<int> actionticks;
    int actions_per_sec=-1;
    Move move;
    vector<string> info;
    int number_of_groups=0;
  };
  static const auto t_unit_size=sizeof(t_unit);
  #ifdef Adler
    void record(){
      static bool qaplite_enabled=file_get_contents("run_qaplite.txt")=="YES";
      if(!qaplite_enabled)return;
      if(replay.capacity()!=game.tickCount)replay.reserve(game.tickCount+16);
      auto&b=qap_add_back(replay);
      //b.vehs=vehs;
      b.sim_w=std::move(sim_w);sim_w=t_world();
      b.w=w;
      b.sim_move=sim_move;
      //b.vehs.shrink_to_fit();
      b.sim_w.shrink_to_fit();b.w.shrink_to_fit();
      b.actionticks=actionticks;b.actionticks.shrink_to_fit();
      b.actions_per_sec=actions_per_sec;
      b.me=me;
      b.op=op;
      b.objs=objs;b.objs.shrink_to_fit();
      b.info=info;
      b.info.shrink_to_fit();
      b.number_of_groups=groups.size();
    }
    vector<t_world_log> replay;
  #else
    void record(){}
  #endif

  bool maybe_later=false;
  void later(){maybe_later=true;}
  
  struct t_waiter{
    bool passed=false;
    int curtime_aft_cond=-1;
    void update(int&wait,const int&curtime){
      if(!passed){passed=true;curtime_aft_cond=curtime;}
      wait=curtime_aft_cond;
    }
    void reset(){passed=false;};
  };

  struct t_attack_state{
    bool hp_bad=false;
    t_waiter waiter_maxpack_hpbad;
    t_waiter waiter_bef_npbad;
    t_waiter waiter_hpbad_beg;

    t_waiter waiter_scale_fast;
    t_waiter waiter_rot;
    t_waiter waiter_scale_after_rot;
    t_waiter sync_before_algo;
  };

  struct t_real_with_id{
    int id;
    real value;
    real&set(int id){this->id=id;return value;}
  };
  DEF_PRO_SORT_BY_FIELD(sort_by_value,t_real_with_id,value);

  static real get_danger(t_world&w)
  {
    static const auto min_d=4.0;static const auto sqr_min_d=min_d*min_d;
    static auto table=t_exchange_table().get();
    auto U=w.get_team_arr(1);//int un=U.size();
    auto E=w.get_team_arr(0);//int en=E.size();
    real out=0;real out2=0;
    auto e_nuke_ready=w.nuke_b.rcd<=60;
    auto func=[&](t_unit&u,int i)
    {
      if(!u.selected)return;
      auto func_me=[&](t_unit&e,int j)
      {
        real sign=+1;
        if(e_nuke_ready&&e.type!=VA){
          sign=-0.1;
        }
        auto q=-0.1*0.002*0.03*(e.type==VA?1.2:1.0);
        auto sqr_dist=u.pos.sqr_dist_to(e.pos);
        if(sqr_dist<sqr_min_d)sqr_dist=sqr_min_d;
        auto f=q/sqr_dist;
        out2+=f*sign;
      };
      if(u.air)U.for_each(func_me,i+1);
      auto func_op=[&](t_unit&e,int j)
      {
        auto q=-table.get_koef(u.type,e.type);
        auto d=u.pos.dist_to(e.pos);
        if(d<min_d)d=min_d;
        if(q<0)q*=10+(100-e.hp)*0.01*30;// mul force to weak enemy
        if(q>0)q*=(0.05+e.hp*0.01*0.95)*2;
        auto f=q/d;
        out+=f;
      };
      E.for_each(func_op);
    };
    U.for_each(func);
    int gg=1;
    return (out+out2);
  };
  static real get_unit_max_capture_f(){
    t_building obj;
    return obj.get_score(vec2d(0,0));
  };
  real get_objs_field_value(t_world&w)
  {
    QAP_PERF("get_objs_field_value");
    static const auto umcf=get_unit_max_capture_f();
    static const auto max_cap=game.maxFacilityCapturePoints;
    auto U=w.lows;int un=U.size();
    real out=0;real out2=0;auto obj_r=get_obj_size().x*0.5;
    auto fmass=3.1;auto cmass=0.05;
    auto&arr=w.objs;
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];auto p=ex.pos;
      if(ex.capturePoints>=max_cap)continue;
      real f=0;
      for(int i=0;i<un;i++)
      {
        auto&u=U[i];
        //if(!u.selected)continue;
        f+=ex.get_score(u.pos);
      }
      auto ooid=ex.ownerPlayerId;
      real ck=ex.capturePoints/real(max_cap);
      real fk=ex.type==FacilityType::CONTROL_CENTER?cmass:fmass;
      real interest=1.0;
      if(ck<0)interest=0.5;
      //if(ck<0&&ooid==op.id)interest=0.5;
      //if(ck<0&&ooid!=op.id)interest=0.6;
      //if(ck>0&&ooid==me.id){interest=2.0+1.5*fabs(ck);}
      //if(ck>0&&ooid!=me.id){interest=1.0+0.2*fabs(ck);}
      //out+=/*(1.0-ck*0.5)*/fk*f*interest;//*(ck<0?1.0-0.5*fabs(ck):0.5+0.5*fabs(ck)*sign);
      out+=fk*f;
    }
    out2=(w.ofv_control_product*cmass+w.ofv_factory_product*fmass)*42*umcf;
    int gg=1;
    return (out+out2);
  }
  bool dominated(){
    auto mesp=getSP(VehicleType::_UNKNOWN_,true);
    auto opsp=getSP(VehicleType::_UNKNOWN_,false);
    return (mesp.n>opsp.n*2.5)&&(mesp.gethp()>opsp.gethp()*2.5)&&mesp.n>200;
  }
  
  struct t_score{
    int id=-1;
    real ofv=0;
    real danger=0;
    real score_diff=0;
    real cur_power_diff=0;
    real cdn=0;
    real limiteds=0;
    bool air;
    void set_from(bool air,t_app&app,t_world&tmp,int id=-1)
    {
      this->air=air;
      this->id=id;
      {
        QAP_PERF("get_danger");
        danger=get_danger(tmp)*(1024/8)/32;
      }
      ofv=app.get_objs_field_value(tmp)*(1024/8);
      score_diff=tmp.get_score_diff()*100*1024;
      cur_power_diff=tmp.get_cur_power_diff()*1024;
      cdn=tmp.cdn*10.0;
      limiteds=tmp.limiteds*5.0;
    }
    real get_minor_value()const{
      return ofv+danger/*+cdn+limiteds*/;
    }
    bool operator<(const t_score&ref)const{
      #define MAJOR(field)if(field!=ref.field)return field<ref.field;
      if(!air)
      {
        //MAJOR(score_diff);
        MAJOR(cur_power_diff);
        //MAJOR(cdn);
        //MAJOR(limiteds);
        //MAJOR(ofv);
        //MAJOR(danger);
        MAJOR(get_minor_value());
      }else{
        //MAJOR(score_diff);
        MAJOR(cdn);
        MAJOR(limiteds);
        MAJOR(cur_power_diff);
        //MAJOR(ofv);
        //MAJOR(danger);
        MAJOR(get_minor_value());
      }
      #undef MAJOR
      return danger<ref.danger;
    }
    //t_score&set(int id){this->id=id;return *this;}
  };

  t_score world2score(bool air,t_world&tmp)
  {
    t_score out;
    out.set_from(air,*this,tmp);
    return out;
  }

  //real world2score(t_world&tmp){
  //  real danger=0;
  //  {
  //    QAP_PERF("get_danger");
  //    danger=get_danger(tmp)*(1024/8)/32;
  //  }
  //  auto ofv=get_objs_field_value(tmp)*(1024/8);
  //  auto score_diff=tmp.get_score_diff()*100*1024;
  //  return score_diff+tmp.get_cur_power_diff()*1024+ofv+danger+tmp.cdn*10.0+tmp.limiteds*5;
  //  /*
  //  old:
  //  auto danger=get_danger(tmp)*1000;// about -20 at start ...
  //  return tmp.get_cur_power_diff()*1000+danger+tmp.cdn*10.0+tmp.limiteds*5; // limiteds = 1173 at start;  cdn=77 at start
  //  */
  //};

  struct t_plan_rec{
    int tick=-1;t_move move;
    t_plan_rec with_offset(int offset)const{t_plan_rec out=*this;out.tick+=offset;return out;}
  };
  struct t_plan{
    vector<t_plan_rec> arr;
    t_plan&add(int tick,const t_move&move){auto&b=qap_add_back(arr);b.tick=tick;b.move=move;return *this;}
    struct t_rec{bool ok;t_plan_rec pr;};
    t_rec get_rec(int tick)const{
      for(int i=0;i<arr.size();i++){auto&ex=arr[i];if(tick==ex.tick){return {true,ex};}}
      return {false};
    }
    t_plan get_promoted()const
    {
      t_plan out;
      for(int i=0;i<arr.size();i++)
      {
        auto&ex=arr[i];
        if(ex.tick<1)continue;
        auto&b=qap_add_back(out.arr);
        b=ex;
        b.tick--;
      }
      return out;
    }
    operator bool()const{return !arr.empty();}
    static void test(){
      t_plan plan;t_move a,b;a.type=777;b.type=888;
      plan.add(0,a);
      QapAssert(plan.get_rec(0).ok);
      QapAssert(plan.get_rec(0).pr.move.type==a.type);
      QapAssert(!plan.get_rec(1).ok);
      plan.add(1,b);
      QapAssert(plan.get_rec(1).ok);
      QapAssert(plan.get_rec(0).pr.move.type==a.type);
      QapAssert(plan.get_rec(1).pr.move.type==b.type);
      QapAssert(!plan.get_rec(2).ok);
      auto p=plan.get_promoted();
      QapAssert(p.get_rec(0).ok);
      QapAssert(p.get_rec(0).pr.move.type==b.type);
      QapAssert(!p.get_rec(1).ok);
      int gg=1;
    }
  };
  static bool vehtype_is_same(VehicleType like_any_when_unknow,VehicleType value){
    if(like_any_when_unknow==VehicleType::_UNKNOWN_)return true;
    return like_any_when_unknow==value;
  }
  struct t_group{
    VehicleType WHO;
    t_attack_state state;
    int curtime=0;
    int wait=0;
    int end_t=-1;
    int groupid=-1;
    vector<int> ids;
    bool strong_start=false;
    bool air_pack=false;
    real priority=1.0;
    void update_ids(t_world&w,t_env&env)
    {
      QAP_PERF("t_group::update_ids");
      vector<int> new_ids;
      new_ids.reserve(ids.size());
      auto arr=w.get_sel_ids(true);
      for(int i=0;i<arr.size();i++){
        auto id=arr[i];
        if(!qap_includes(ids,id)&&env.id2groupid[id]>=0)continue;
        if(!vehtype_is_same(WHO,env.id2veh(id)->type))continue;
        qap_add_back(new_ids)=id;
      }
      ids=new_ids;
    }
  };
  struct t_sel_quad{
    int n;
    vec2d pos;vec2d size;
  };
  //t_suppos get_suppos_by_ids_impl(const vector<bool>&ids){
  //  auto one=vec2d(1,1);
  //  t_suppos out;out.minp=+one*1e6;out.maxp=-one*1e6;
  //  QAP_FOREACH(vehs,{
  //    if(our!=is_our(ex)||(ex.type!=type))return;
  //    out.n++;
  //    out.moved+=is_moved(ex);
  //    out.updated+=id2updated[ex.id];
  //    out.superpos+=get_pos(ex);
  //    out.superspd+=get_spd(ex);
  //    out.superhp+=ex.durability;
  //    out.selected+=ex.selected;
  //    vec2d::comax(out.maxp,get_pos(ex));
  //    vec2d::comin(out.minp,get_pos(ex));
  //  });
  //  return out;
  //}
  t_sel_quad get_sel_quad(const vector<int>&ids){
    auto one=vec2d(1,1);
    t_suppos out;out.minp=+one*1e6;out.maxp=-one*1e6;
    for(int i=0;i<ids.size();i++){
      auto id=ids[i];
      auto*p=id2veh(id);
      if(!p||p->durability<=0)continue;
      auto&ex=*p;
      out.n++;
      vec2d::comax(out.maxp,get_pos(ex));
      vec2d::comin(out.minp,get_pos(ex));
    }
    t_sel_quad q={out.n,out.getcenter(),out.getsize()};
    return q;
  }

  t_move mk_rect(vec2d pos,vec2d size,VehicleType type=VehicleType::_UNKNOWN_){
    t_move cmd;
    cmd.type=t_cmds::t_rect::cmd_id;
    cmd.rect.add=false;
    cmd.rect.pos=pos;
    cmd.rect.size=size;
    cmd.rect.type=type;
    return cmd;
  }

  t_move mk_rect(t_group&group){
    auto q=get_sel_quad(group.ids);
    t_move cmd;
    cmd.type=t_cmds::t_rect::cmd_id;
    cmd.rect.add=false;
    cmd.rect.pos=q.pos;
    cmd.rect.size=q.size+vec2d(1,1)*game.vehicleRadius;
    cmd.rect.type=group.WHO;
    return cmd;
  }

  void group_upd(t_group&g)
  {
    QAP_FOREACH(g.ids,id2groupid[ex]=g.groupid);
  }

  /*
  when
  for each groups
  ex.t
  */

  vector<t_group> groups;
  t_plan cur_plan;
  vector<int> actionticks;
  int actions_per_sec=-1;
  int ticks_per_sec=60;

  PRO_FUNCGEN_GETP_BY_FIELD(t_group,groupid2group,groups,int,groupid);
  
  void before_move(){
    actions_per_sec=game.baseActionCount;
    ticks_per_sec=game.actionDetectionInterval;
    QAP_FOREACH(objs,if(ex.ownerPlayerId==me.id&&ex.type==FacilityType::CONTROL_CENTER)actions_per_sec+=game.additionalActionCountPerControlCenter);
    clean_if(actionticks,[&](const int&v){return v+ticks_per_sec<=world.tickIndex;});
  }
  void after_move()
  {
    if(me.remainingActionCooldownTicks)return;
    if(move.action==ActionType::_UNKNOWN_)return;
    actionticks.push_back(world.tickIndex);
    //actionticks.push_back();
    #ifdef Adler
    if(replay.size())replay.back().move=move;
    #endif
  }

  bool action_ready(const vector<int>&arr)const{return arr.size()<actions_per_sec;}

  bool two_actions_ready_in_next_tick()const{
    auto arr=actionticks;
    int t=world.tickIndex;
    arr.push_back(t);
    t++;
    clean_if(arr,[&](const int&v){return v+ticks_per_sec<=t;});
    return action_ready(arr);
  }
  static bool n_actions_ready_in_next_tick(const vector<int>&actionticks,int n,int tickIndex,int ticks_per_sec,int actions_per_sec){
    auto arr=actionticks;
    int t=tickIndex;
    for(int i=1;i<n;i++){arr.push_back(t);t++;}
    clean_if(arr,[&](const int&v){return v+ticks_per_sec<=t;});
    return arr.size()<actions_per_sec;
  }
  static int how_much_actions_ready_in_next_ticks(const vector<int>&actionticks,int tickIndex,int ticks_per_sec,int actions_per_sec){
    for(int i=1;i<actions_per_sec;i++){
      if(!n_actions_ready_in_next_tick(actionticks,i,tickIndex,ticks_per_sec,actions_per_sec))return i-1;
    }
    return actions_per_sec;
  }
  bool n_actions_ready_in_next_tick(int n)const{
    auto arr=actionticks;
    int t=world.tickIndex;
    for(int i=1;i<n;i++){arr.push_back(t);t++;}
    clean_if(arr,[&](const int&v){return v+ticks_per_sec<=t;});
    return action_ready(arr);
  }

  bool nuclear_allowed()const{return !me.remainingNuclearStrikeCooldownTicks;}

  bool try_strike(){
    return false;
  }

  bool host_selected(){
    bool found=false;
    QAP_FOREACH(vehs,if(ex.selected&&is_our(ex)&&ex.id==me.nextNuclearStrikeVehicleId)found=true);
    return found;
  }

  bool nuke_alarm()const{
    return op.nextNuclearStrikeTickIndex>=0||me.nextNuclearStrikeTickIndex>=0;
  }
  
  int NEAR_UNIT_ID_TO_POINT_BY_TYPES(vec2d pos,const char*types,bool our){
    return QAP_MINVAL_ID_OF_VEC(vehs,(our!=is_our(ex)||!any_vtype_of(ex,types))?1e9:get_pos(ex).dist_to(pos));
  };

  void do_full_nuke()
  {
    /*
    ce.init(...);
    w.foreach_enemy_unit
    e is t_unit
    ce.add(&e);
    ce.foreach_not_empty_cell
    c is t_cell
    func(t_cell){
      
    };
    ce.nine_nb(c.coords,func);
    
    c.foreach
    p is t_unit*
    */
  }
  t_move do_nuke_impl(t_group&group)
  {
    const auto r=game.vehicleRadius;
    for(;;)
    {
      auto sq=get_sel_quad(group.ids);
      vec2d host_pos=sq.pos;
      int dirs=24;
      auto arr=t_move::get_movdirs_norm(16);
      auto eid=NEAR_UNIT_ID_TO_POINT_BY_TYPES(host_pos,"FHATI",false);
      if(eid<0||vehs[eid].type==VA||is_our(vehs[eid]))break;
      auto&e=vehs[eid];
      auto epos=get_pos(e);
      auto id=NEAR_UNIT_ID_TO_POINT_BY_TYPES(host_pos,"FHATI",true);
      auto&u=vehs[id];
      auto vision_range=get_vis_k(get_pos(u),u.aerial)*get_vis_range(u.type)-0.001;
      if(!epos.dist_to_point_less_that_r(get_pos(u),vision_range))break;

      auto tmp=w;
      vector<real> u_vr_arr;
      vector<vec2d> u_pos_arr;
      for(int i=0;i<30;i++){
        auto*phost=tmp.get_phost(u.id);
        if(!phost)return t_move();
        qap_add_back(u_pos_arr)=phost->pos;
        qap_add_back(u_vr_arr)=get_vis_k(phost->pos,u.aerial)*get_vis_range(u.type)-0.001;
        tmp.update(*this,1,true);
      }
      auto tmp_cur_ehp=tmp.get_cur_team_power(false);
      vector<real> out;vector<vec2d> points;
      //static real op_dmg_exp_max=-1;
      //static real op_dmg_p_max=-1;
      //static real op_dmg_max=-1;
      //static real procent_max=-1;
      //static real pred_procent_max=-1;
      auto fog=game.fogOfWarEnabled;
      auto use_dir=[&](const vec2d&ex,real koef){
        auto p=epos+ex*koef;
        bool ok=true;
        QAP_FOREACH(u_pos_arr,ok=ok&&p.dist_to_point_less_that_r(ex,u_vr_arr[i]));
        if(!ok)return;
        auto me_dmg=tmp.get_nuclear_dmg(*this,p,true);
        auto op_dmg_exp=w.get_expected_nuclear_dmg(*this,p,false);
        auto op_dmg_p=fog?0:tmp.get_nuclear_dmg(*this,p,false);
        auto op_dmg=fog?op_dmg_exp:(op_dmg_exp+op_dmg_p)*0.5;

        //op_dmg_exp_max=std::max(op_dmg_exp_max,op_dmg_exp);
        //op_dmg_p_max=std::max(op_dmg_p_max,op_dmg_p);
        //op_dmg_max=std::max(op_dmg_max,op_dmg);
        //procent_max=std::max(procent_max,op_dmg/tmp_cur_ehp);
        //pred_procent_max=std::max(pred_procent_max,op_dmg_p_max/tmp_cur_ehp);

        if(!fog)if(op_dmg<tmp_cur_ehp*0.06&&op_dmg<3000)return;
        if( fog)if(op_dmg<600)return;
        qap_add_back(points)=p;
        qap_add_back(out)=me_dmg-op_dmg;//tmp.get_nuclear_dmg_diff(*this,p);
      };
      {
        QAP_PERF("do_nuke::loops");
        QAP_FOREACH(arr,use_dir(ex,r*2*5*0.5));
        QAP_FOREACH(arr,use_dir(ex,r*2*5*1.0));
        QAP_FOREACH(arr,use_dir(ex,r*2*5*1.5));
        QAP_FOREACH(arr,use_dir(ex,r*2*5*2.0));
      }
      auto best_id=QAP_MINVAL_ID_OF_VEC(out,ex);
      if(best_id<0||out[best_id]>0)break;
      auto p=points[best_id];
      t_move cmd;
      cmd.type=t_cmds::t_bomb::cmd_id;
      auto&bomb=cmd.bomb;
      bomb.veh_id=u.id;
      bomb.pos=p;
      return cmd;
    }
    return t_move();
  }
  struct t_nuke_strike_rec{
    t_cmds::t_bomb bomb;
    bool ok;
    t_score value;
  };
  void do_nuke()
  {
    if(!nuclear_allowed())return;
    if(me.remainingActionCooldownTicks)return;
    QAP_PERF("do_nuke");
    auto inf=1024*1024;
    vector<t_move> rs;
    QAP_FOREACH(groups,if(get_sel_quad(ex.ids).n)qap_add_back(rs)=do_nuke_impl(ex));
    clean_if(rs,[](t_move&m){return m.type<0;});
    vector<t_nuke_strike_rec> recs;
    QAP_FOREACH(rs,qap_add_back(recs)=nuke_sim(ex.bomb));
    clean_if(recs,[](t_nuke_strike_rec&ex){return !ex.ok;});
    auto bestid=QAP_MINVAL_ID_OF_VEC(recs,ex.value);
    if(bestid<0)return;
    auto&win=recs[bestid];
    move=win.bomb.get();
  }
  t_nuke_strike_rec nuke_sim(t_cmds::t_bomb&bomb)
  {
    QAP_PERF("nuke_sim");
    auto tmp=w;
    tmp.use(bomb,true);
    tmp.use(mk_rect(bomb.pos,vec2d(1,1)*game.tacticalNuclearStrikeRadius*4.0),false);
    tmp.use(mk_scale(bomb.pos,2),false);
    for(int i=0;i<tmp.nuke_delay;i++){
      tmp.update(*this,1,true);
    }
    int gg=1;
    bool ok=tmp.nuke_a.ticks<0.001;
    t_nuke_strike_rec out={bomb,ok};
    if(ok)out.value=world2score(false,tmp);
    return out;
  }
  struct t_production_rec{
    VehicleType type;
    int n;
    real expand_koef;
    real value;
  };
  int get_number_of_factory(){int n=0;QAP_FOREACH(objs,if(ex.type==FacilityType::VEHICLE_FACTORY)n++);return n;}

  int get_number_of_units_for_creating_new_group(VehicleType type){
    static const int nof=get_number_of_factory();
    int k=3;
    if(nof==1*2)k=2;
    if(nof==2*2)k=3;
    if(nof==3*2)k=3;
    if(nof==4*2)k=3;
    if(nof==5*2)k=3;
    if(nof==6*2)k=4;
    if(nof==7*2)k=4;
    if(nof>7*2)k=4;
    if(type==VI)return 11*k;
    if(type==VT)return 11*k;
    if(type==VH)return 11*k;
    if(type==VF)return 11*k;
    return 11*k;
  }
  VehicleType get_target_producation_type(){
    vector<t_production_rec> arr;
    #define F(TYPE,N,K){auto&b=qap_add_back(arr);b.type=TYPE;b.n=N;b.expand_koef=K;};
    for(;;)
    {
      static const int nof=get_number_of_factory();
      F(VI,11*3,1.0);
      F(VT,11*3,3.0);
      F(VF,11*3,0.5);
      F(VH,11*3,0.5);
      //if(false)if(nof<=4)
      //{
      //  F(VI,100,1.0);break;
      //}
      //F(VT,100,1.0);break;
      break;
    }
    //F(VF,40,1.0);
    //F(VH,40,1.0);
    //F(VA,20,1.0);
    //F(VT,20,1.0);
    /*
    F(VI,20,1.0);
    //F(VF,40,1.0);
    F(VH,5,1.0);
    //F(VA,20,1.0);
    F(VT,15,1.0);
    */
    #undef F
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      if(getSP(ex.type).n<ex.n)return ex.type;
    }
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      auto extra_n=getSP(ex.type).n-ex.n;
      ex.value=extra_n/(ex.n*ex.expand_koef);
    }
    auto win=QAP_MINVAL_ID_OF_VEC(arr,ex.value);
    return arr[win].type;
  }
  void do_setup_producation()
  {
    if(!objs.size())return;
    if(me.remainingActionCooldownTicks)return;
    if(!n_actions_ready_in_next_tick(3))return;
    auto&arr=world.facilities;
    const auto targer_veh_type=get_target_producation_type();
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      bool a=is_our(ex);
      bool b=FacilityType::VEHICLE_FACTORY==ex.type;
      bool ok=a&&b;
      if(!ok)continue;
      //if(targer_veh_type==ex.vehicleType)continue;
      if(VehicleType::_UNKNOWN_!=ex.vehicleType)continue;
      move.action=ActionType::SETUP_VEHICLE_PRODUCTION;
      move.vehicleType=targer_veh_type;
      move.facilityId=ex.id;
      return;
      break;
    }
    if(new_group_added_from_factorys_with_ids.empty())return;
    auto fid=new_group_added_from_factorys_with_ids.back();
    new_group_added_from_factorys_with_ids.pop_back();
    auto*p=id2obj(fid);
    if(!p)return;
    if(targer_veh_type==p->vehicleType)return;
    move.action=ActionType::SETUP_VEHICLE_PRODUCTION;
    move.vehicleType=targer_veh_type;
    move.facilityId=p->id;
  }
  real crutch_nuke_group_actions=1;
  real get_number_of_group_actions(){
    real total=0;
    QAP_FOREACH(groups,total+=ex.priority);
    return total;
  }
  int get_cur_gap(){
    int GAP=6*5*2*2;
    auto noga=get_number_of_group_actions();
    real rGAP=(noga+crutch_nuke_group_actions)*(noga>1?2:1)*real(ticks_per_sec)/actions_per_sec;
    GAP=rGAP;
    if(GAP<rGAP)GAP++;
    return GAP;
  }
  int get_gap(t_group&g){
    auto gap=get_cur_gap();
    if(g.priority<=0)return gap;
    real rGAP=gap/g.priority;
    int GAP=rGAP;
    if(GAP<rGAP)GAP++;
    return GAP;
  }
  int get_max_gap(){
    int id=QAP_MINVAL_ID_OF_VEC(groups,ex.priority);
    return id<0?get_cur_gap():get_gap(groups[id]);
  }
  static t_move mk_mov(vec2d dir){t_move out;out.type=out.mov.cmd_id;out.mov.dir=dir;return out;};
  static t_move mk_scale(vec2d pos,real factor){t_move out;out.type=out.scale.cmd_id;out.scale.factor=factor;out.scale.pos=pos;return out;};
  #define FOREACH_TYPE(TYPES_AS_STR,CODE){\
    auto*ug_tmp_ptr_with_types=TYPES_AS_STR;\
    for(;*ug_tmp_ptr_with_types;){const auto ex=CharToVehicleType(*ug_tmp_ptr_with_types);{CODE;};ug_tmp_ptr_with_types++;}\
  }

  vector<int> filter_ids(const vector<int>&arr,VehicleType type){
    vector<int> out;
    out.reserve(arr.size());
    for(int i=0;i<arr.size();i++){
      auto id=arr[i];
      if(auto*p=id2veh(id))if(p->type==type){
        qap_add_back(out)=id;
      }
    }
    return out;
  }

  void test2(){
    t_world w=this->w;
    auto tmp=w.objs;w.objs.resize(0);
    w.get_arr().for_each([](t_unit&ex,int id){ex.hp=0;});
    w.update(*this,1,true);
    w.objs=tmp;
    w.objs.resize(1);
    w.objs[0].capturePoints=100-game.facilityCapturePointsPerVehiclePerTick;
    {
      auto&b=qap_add_back(w.lows);
      b.pos=w.objs[0].pos;
      b.air=false;
      b.type=VT;
      b.att_cdt=0;
      b.hp=100;
      b.our=true;
      b.end=vec2d(0,0);
    }
    for(;;){
      auto&building=w.objs[0];
      auto bef_score=world2score(false,w);
      w.update(*this,1,true);
      auto score=world2score(false,w);
      int gg=1;
    }
  }
  vector<int> new_group_added_from_factorys_with_ids;
  void do_move()
  {
    //test2();
    //if(world.tickIndex){
    //  //for(int i=0;i<GAP;i++){
    //    w.update(*this);
    //  //}
    //}

    if(!world.tickIndex)
    {
      auto tmp=w;
      auto add=[&](VehicleType WHO){
        auto&b=qap_add_back(groups);
        b.WHO=WHO;
        tmp.sel_by_type(WHO);
        b.ids=tmp.get_sel_ids(true);
        b.groupid=new_group();
        b.strong_start=any_vtype_of(WHO,"FHA");//true;
        if(b.WHO==VF)b.priority=2;
        if(b.WHO==VH){b.priority=2;b.end_t=250;}
        if(b.WHO==VA)b.priority=1;
        if(b.WHO==VT)b.priority=1;
        return b;
      };
      if(bool need_air_test=false&&!objs.size()&&!game.fogOfWarEnabled)
      {
        FOREACH_TYPE("F",add(ex));crutch_nuke_group_actions=0;
      }else{
        FOREACH_TYPE("FHITA",add(ex));
      }
    }
    {
      int GAP=get_max_gap();
      this->w.set_enemy_end_pos(GAP);
    }
    /*
    if(world.tickIndex>700)
    {
      sim_w=w;
      for(int i=0;i<50;i++){
         sim_w.update(*this,1,true);
      }
    }
    //return;
    */
    
    static int prev_gid=-1;
    static bool sim_attack=true;

    if(cur_plan)
    {
      auto rec=cur_plan.get_rec(0);
      QapAssert(rec.ok);
      auto mv=rec.pr.move;
      w.use(mv,true);
      move=mv.get();
      cur_plan=cur_plan.get_promoted();
      prev_gid=-1;
      return;
    }
    if(nuke_alarm())
    {
      if(!two_actions_ready_in_next_tick())return;
      auto func=[&](const Player&pp,int&prev){
        auto cur=pp.nextNuclearStrikeTickIndex;
        if(cur<0)return false;
        if(prev==cur)return false;
        prev=cur;
        QAP_PERF("nuke_brain");
        nuke_brain(groups,w.nuke_delay*2,sim_attack);
        return true;
      };
      static int op_prev_tick=-1;
      static int me_prev_tick=-1;
      if(func(op,op_prev_tick))return;
      //if(func(me,me_prev_tick))return;
    }

    if(world.tickIndex%12==11){do_nuke();if(move.action!=ActionType::_UNKNOWN_)return;}
    if(world.tickIndex%12==10){do_setup_producation();if(move.action!=ActionType::_UNKNOWN_)return;}

    //if((world.tickIndex/2)%6==5)return; // <--- dont change this. see HOT_FIX_20171126_11_51
    if(!n_actions_ready_in_next_tick(3))return;

    #define return_later(){later();return;}
    #define NW(CODE){if(curtime<wait)return_later();if(curtime<=wait){CODE;return_later();}wait++;}

    #define ROT_TO_EBASE_NOWAIT(WHO){\
      vec2d edir(1,1);vec2d curdir(1,0);\
      /*NW(act_select(WHO));*/\
      NW(act_rot(GP(WHO),edir.Rot(curdir).GetAng()));\
    }

    #define WAIT_STOP_FOR_V2(WHO,MEM)WAIT_WHEN(getSP(WHO).moved,MEM)

    #define WAIT_WHEN(CONDITIONS,MEM){\
      t_waiter&tmp=MEM;\
      if(!tmp.passed){\
        if(CONDITIONS)return_later();\
        tmp.curtime_aft_cond=curtime;\
        tmp.passed=true;\
      }\
      wait=tmp.curtime_aft_cond;\
    }
    #define WAIT_SYNC(MEM){\
      t_waiter&tmp=MEM;\
      if(!tmp.passed){\
        tmp.curtime_aft_cond=curtime;\
        tmp.passed=true;\
      }\
      wait=tmp.curtime_aft_cond;\
    }

    #define MAXPACK_NOWAIT(WHO){SCALE_NOWAIT(WHO,0.85);}
    #define SCALE_NOWAIT(WHO,K){/*NW(act_select(WHO));*/NW(/*move.maxSpeed=0*max_speed(VT)/*1.0425*/;act_scale(GP(WHO),K));}

    #define STATIC(TYPE,NAME,VALUE)TYPE&NAME=group.state.NAME;
    
    auto enemy_have_any=[&](const char*ENEMYTYPES)
    {
      int n=string(ENEMYTYPES).size();
      FOREACH_TYPE(ENEMYTYPES,if(!getSP(ex,false).n)n--;);
      return n;
    };
    
    auto sel_rect_by_type=[&](VehicleType type,vec2d pos,vec2d size){
      t_move out;
      out.type=t_cmds::t_rect::cmd_id;
      out.rect.add=false;
      out.rect.pos=pos;out.rect.size=size;
      out.rect.type=type;
      return out;
    };
    if(bool need_mk_group_from_factory=true)
    {
      auto tmp=w;
      auto size=get_obj_size();
      auto&arr=world.facilities;
      for(int i=0;i<arr.size();i++)
      {
        auto&ex=arr[i];
        if(!is_our(ex)||ex.type!=FacilityType::VEHICLE_FACTORY)continue;
        auto objp=get_pos(ex);
        tmp.use(sel_rect_by_type(VehicleType::_UNKNOWN_,objp,size),true);
        vector<int> ids,fails;
        vector<int> types;types.resize(int(VehicleType::_COUNT_)+1,0);
        auto func=[&](t_unit&u,int id)
        {
          if(!u.selected)return;
          int ugid=id2groupid[u.id];
          if(ugid>=0){qap_add_back(fails)=u.id;return;}
          qap_add_back(ids)=u.id;
          types[int(u.type)]++;
        };
        tmp.get_team_arr(true).for_each(func);
        auto tid=QAP_MINVAL_ID_OF_VEC(types,-ex);
        auto major_type=(VehicleType)tid;
        if(ids.size()<get_number_of_units_for_creating_new_group(major_type))
        {
          if(types[tid]!=ids.size())continue;
          if(fails.size()&&ids.size()>10)
          {
            auto groupid=id2groupid[fails[0]];
            if(auto*pg=groupid2group(groupid))
            {
              if(pg->WHO!=major_type)continue;
              pg->ids+=ids;
              group_upd(*pg);
              continue;
            }
          }
          continue;
        }
        //if(types[tid]!=ids.size()){
        //  major_type=VehicleType::_UNKNOWN_;
        //  //WTF we have news units with difirence types...
        //  //b.WHO=VehicleType::_UNKNOWN_;
        //  //ids+=fails;
        //}
        auto&b=qap_add_back(groups);
        b.WHO=major_type;
        b.ids=filter_ids(ids,major_type);
        b.groupid=new_group();
        b.priority=any_vtype_of(b.WHO,"FH")?2:1;
        static int packed_counter=0;packed_counter++;
        b.air_pack=any_vtype_of(b.WHO,"FH")||packed_counter%2;
        group_upd(b);
        qap_add_back(new_group_added_from_factorys_with_ids)=ex.id;
        //QAP_FOREACH(vehs,if(is_our(ex))return;auto d=(get_pos(ex)-objp).fabs();return d.x<size&&d.y<size);
      }
    }

    if(bool fast_debug=0)
    {
      if(!sim_attack&&w.get_cur_power_diff())sim_attack=true;
      if(!sim_attack)return;
    }
    struct t_best_result{
      int rs_id;
      t_world w;
      t_move move;
      real value;
    };
    struct t_update_result{
      t_plan plan;
      t_best_result result;
    };
    
    auto DO_ATTACK=[&](t_group&group)
    {
      auto WHO=group.WHO;
      auto&curtime=group.curtime;
      auto&wait=group.wait;

      //checks
      //if(!enemy_have_any(ENEMYTYPES))return;
      
      if(group.strong_start)
      {
        STATIC(t_waiter,waiter_scale_fast,t_waiter());
        STATIC(t_waiter,waiter_rot,t_waiter());
        STATIC(t_waiter,waiter_scale_after_rot,t_waiter());
      
        NW(act_scale(w.getSP(true).getpos(),0.85));
        WAIT_STOP_FOR_V2(WHO,waiter_scale_fast);

        if(WHO!=VA){
          ROT_TO_EBASE_NOWAIT(WHO);
          WAIT_STOP_FOR_V2(WHO,waiter_rot);
        }
        NW(move.maxSpeed=max_speed(VT);act_scale(GP(WHO),0.1));
        WAIT_STOP_FOR_V2(WHO,waiter_scale_after_rot);
      }
      if(group.air_pack&&!group.strong_start)
      {
        NW(act_scale(w.getSP(true).getpos(),0.1));
      }
      //auto eid=NEAR_UNIT_ID_TO_POINT_BY_TYPES(GP(WHO),ENEMYTYPES,false);
      //vec2d epos=get_pos(vehs[eid]);
      //vec2d espd=get_spd(vehs[eid]);
      //epos+=espd*25;
      //auto dir=epos-WHO_POS;
      //w.sel_clear();
      //w.sel_by_type(WHO);
      if(!w.sel_count(true)){
        group.ids.clear();
        return;
      }
      auto get_dirs=[&](int t)->int{
        //return 4;
        if(t<600)return 8;
        if(t>10*1000&&vehs.size()>800)return 8;
        if(t>15*1000&&vehs.size()>500)return 8;
        return 16;
      };
      auto GAP=get_gap(group)+(group.priority>1?8:0)*0;//std::max<int>(get_gap(group),get_cur_gap());
      auto len=1;int dirs=get_dirs(world.tickIndex);
      
      t_move def_move;def_move.type=-1;
      vector<t_move> rs;
      rs.push_back(def_move);
      //auto group_pos=w.getSP(true).getpos();
      //if(w.nuke_a)qap_add_back(rs)=mk_scale(w.nuke_a.pos,1.0*1.2);
      //if(w.nuke_b)qap_add_back(rs)=mk_scale(w.nuke_b.pos,1.0*1.2);
      //qap_add_back(rs)=mk_scale(group_pos,1.0*1.2);
      //qap_add_back(rs)=mk_scale(group_pos,1.0/1.2);
      auto slowest_unit_type=WHO==VehicleType::_UNKNOWN_?w.get_sel_slowest_type(*this,true):WHO;
      rs+=t_move::get_mov_set_v3(*this,slowest_unit_type,GAP*len,1,dirs); // <-------------------- get_mov_set_v3 HERE ------------------------------->

      auto tmp=this->w;
      struct t_sim_out{
        real power_diff;
        real danger;
        int cdn;
        int lim;
      };
      auto sim=[&](int id,t_move m,int sim_iters,int GAP)->t_score
      {
        real LEN_KOEF=GAP/real(sim_iters);
        tmp=this->w;
        if(m.type>=0)tmp.use(m,true);
        for(int i=0;i<sim_iters*len;i++){
          tmp.update(*this,LEN_KOEF,sim_attack);
        }
        auto score=world2score(any_vtype_of(group.WHO,"FH"),tmp);
        score.id=id;
        return score;
      };

      vector<t_score> out;//out.resize(rs.size());
      QapClock clock;
      int defq_sim_iters=nuke_alarm()?12:4;int maxq_sim_iters=nuke_alarm()?GAP/3:GAP/5; // <-------------------- QUALITY CONFIG HERE
      if(nuke_alarm()&&host_selected()){
        defq_sim_iters=GAP;maxq_sim_iters=GAP;
      }
      QAP_FOREACH(rs,qap_add_back(out)=sim(i,ex,defq_sim_iters,GAP));
      auto qarr=out;
      std::sort(qarr.begin(),qarr.end());
      qarr.resize(std::max<int>(1,out.size()/(dirs/1)));  // <---- qarr = 16*1
      vector<t_score> out2;
      QAP_FOREACH(qarr,qap_add_back(out2)=sim(ex.id,rs[ex.id],maxq_sim_iters,GAP));
      sim_time=clock.MS();
      rs_size=rs.size();
      auto id=QAP_MINVAL_ID_OF_VEC(out2,ex);
      auto&winrec=out2[id];
      auto win=rs[winrec.id];
      #ifdef Adler
      sim(winrec.id,win,maxq_sim_iters,get_max_gap());sim_w=tmp;sim_move=win;
      #endif
      move=win.get();
      w.use(win,true);
      auto u=0;
    };

    maybe_later=false;

    //auto&true_curtime=curtime;
    //auto&true_wait=wait;

    #define IF_LATER_THEN_RETURN()if(maybe_later)return;
    #define CALL(CODE){([&](){CODE;})();IF_LATER_THEN_RETURN();}
    
    auto need_upd=[&](t_group&g)->bool{
      auto n=get_sel_quad(g.ids).n;
      if(!n){
        g.ids.clear();
      }
      return n;
    };
    auto head=[&](t_group&group)
    {
      if(objs.empty()&&world.tickIndex>=300&&group.WHO==VA)
      {
        if(getSP(VF).n+getSP(VH).n>=100&&getSP(VA).n==100){
          group.end_t=get_gap(group)+world.tickIndex;
          return;
        }
      }
      if(prev_gid!=group.groupid)
      {
        if(!n_actions_ready_in_next_tick(2))return;
        //if(world.tickIndex%2)return;
        move=mk_rect(group).get();
        //act_select(group.WHO);
        prev_gid=group.groupid;
        return;
      }
      if(!n_actions_ready_in_next_tick(1))return;
      group.update_ids(w,*this);
      group_upd(group);
      {
        auto gap=get_gap(group);
        group.end_t=world.tickIndex+gap;
      }
      group.curtime++;
      group.wait=1;
      {auto&curtime=group.curtime;auto&wait=group.wait;WAIT_SYNC(group.state.sync_before_algo);}
      DO_ATTACK(group);
    };
    maybe_later=false;
    
    auto inf=1024*1024;
    auto gid=QAP_MINVAL_ID_OF_VEC(groups,!need_upd(ex)?inf:ex.end_t);
    if(gid>=0)
    {
      auto&g=groups[gid];
      if(g.end_t<=world.tickIndex+1)
      {
        head(g);
      }
      //if(any_vtype_of(g.WHO,"FH")&&g.strong_start&&g.priority>1&&w.tickIndex>200)g.priority=1;
    }
    int gg=1;
    clean_if(groups,[](t_group&ex){return ex.ids.empty();});
    //QAP_FOREACH(groups,head(ex));

    /*
    
    nbf.load(this);
    auto subiters=5;
    auto maxiters=1000;
    auto depth=maxiters/subiters;
    nbf.build_tree(depth,subiters);
    auto node_id=QAP_MINVAL_ID_OF_VEC(nbf.nodes,ex.escore-ex.score);
    auto root_move=nbf.get_root_move_from(node_id);
    move=root_move.get_move();

    */
    //test();
    return;
  }
  void hack_for_round1__if_enemy_dont_have_tanks_but_we_have_then_decrease_tank_density(){}
  void nuke_brain(vector<t_group>&groups,int GAP,bool sim_attack)
  {
    struct t_best_result{
      int rs_id;
      t_world w;
      t_move move;
      t_score value;
      int group_id;
    };
    struct t_update_result{
      t_plan plan;
      t_best_result result;
    };

    vector<t_update_result> results;
    
    if(!two_actions_ready_in_next_tick()){
      if(nuclear_allowed())if(try_strike())return;
      return;
    }/*
    auto sel_by_type=[&](VehicleType type){
      t_move out;
      out.type=t_cmds::t_rect::cmd_id;
      out.rect.add=false;
      auto wh=get_wh();
      out.rect.pos=wh*0.5;out.rect.size=wh;
      out.rect.type=type;
      return out;
    };*/
    auto sim_all_then_estimate_and_return_best_result=[&](int group_id,const t_world&src,const vector<t_move>&rs,int len,int dirs)
    {
      auto tmp=src;
      auto sim=[&](const t_move&m,int sim_iters,int id)->t_score
      {
        real LEN_KOEF=GAP/real(sim_iters);
        tmp=src;
        if(m.type>=0)tmp.use(m,true);
        for(int i=0;i<sim_iters*len;i++){
          tmp.update(*this,LEN_KOEF,sim_attack);
        }
        auto score=world2score(false,tmp);
        score.id=id;
        return score;
      };

      vector<t_score> out;//out.resize(rs.size());
      int defq_sim_iters=10;int maxq_sim_iters=GAP/2; // <-------------------- QUALITY [nuke_brain]CONFIG HERE 
      if(auto*phost=tmp.get_phost(src.nuke_a.host_id))if(phost->selected){
        defq_sim_iters=GAP;maxq_sim_iters=GAP;
      }
      QAP_FOREACH(rs,qap_add_back(out)=sim(ex,defq_sim_iters,i));
      auto qarr=out;
      std::sort(qarr.begin(),qarr.end());
      qarr.resize(std::max<int>(1,out.size()/(dirs/1)));  // <---- qarr = 16*1
      vector<t_score> out2;
      QAP_FOREACH(qarr,qap_add_back(out2)=sim(rs[ex.id],maxq_sim_iters,ex.id));
      rs_size=rs.size();
      auto id=QAP_MINVAL_ID_OF_VEC(out2,ex);
      auto&winrec=out2[id];
      auto win=rs[winrec.id];
      //move=win.mov.get();
      //w.use(win);
      //t_move def_move;def_move.type=-1;
      //auto def_score=sim(def_move,maxq_sim_iters);

      t_best_result retval;
      retval.rs_id=winrec.id;
      retval.move=win;
      //base = 0; win = 10; 
      //base = 50; win = 40; .. but why i need think about this shit? may be here is other way to find solution?
      //less_and_negative_and_better-more_and_positive_and_worse
      retval.value=winrec;//winrec.value-out[0].value;
      retval.group_id=group_id;
      return retval;
    };
    auto upd=[&](t_group&ex,int group_id){
      auto tmp=w;
      auto sel_cmd=mk_rect(ex);
      tmp.use(sel_cmd,true);
      int number_of_units=tmp.sel_count(true);
      if(!number_of_units)return;
      if(groups.size()>12&&number_of_units<10)return;
      tmp.update(*this,1,true);

      auto len=1;int dirs=16;

      t_move def_move;def_move.type=-1;
      vector<t_move> rs;
      rs.push_back(def_move);
      //if(w.nuke_a)qap_add_back(rs)=mk_scale(w.nuke_a.pos,1.0*1.2);
      //if(w.nuke_b)qap_add_back(rs)=mk_scale(w.nuke_b.pos,1.0*1.2);
      auto slowest_unit_type=ex.WHO==VehicleType::_UNKNOWN_?w.get_sel_slowest_type(*this,true):ex.WHO;
      rs+=t_move::get_mov_set_v3(*this,slowest_unit_type,GAP*len,1,dirs);

      auto best_result=sim_all_then_estimate_and_return_best_result(group_id,tmp,rs,len,dirs);
      if(best_result.move.type<0)return;
      auto&b=qap_add_back(results);
      b.plan.add(0,sel_cmd).add(1,best_result.move);
      b.result=std::move(best_result);
    };

    QAP_FOREACH(groups,upd(ex,i));

    auto id=QAP_MINVAL_ID_OF_VEC(results,ex.result.value);
    if(id<0)return;
    auto rid=results[id];
    auto&plan=rid.plan;
    if(!plan.get_rec(0).ok)return;
    auto best_cmd=plan.get_rec(0).pr.move;
    move=best_cmd.get();
    w.use(best_cmd,true);
    cur_plan=plan.get_promoted();
    auto&g=groups[rid.result.group_id];
    g.end_t=world.tickIndex+1+GAP;
    g.update_ids(w,*this);
    //g.ids=w.get_sel_ids(true);
    group_upd(g);
    #ifdef Adler
    if(bool need_sim_w=true)
    {
      sim_w=w;
      sim_w.update(*this,1,true);
      auto rec=cur_plan.get_rec(0);
      QapAssert(rec.ok);
      sim_w.use(rec.pr.move,true);
      for(int i=0;i<GAP;i++){
        sim_w.update(*this,1,true);
      }
    }
    #endif
  }

  void test(){
    t_world w;
    {
      auto&b=qap_add_back(w.lows);
      b.pos=vec2d(0,0);
      b.air=false;
      b.type=VT;
      b.att_cdt=0;
      b.hp=100;
      b.our=true;
      b.end=vec2d(0,0);
    }
    {
      auto&b=qap_add_back(w.etops);
      b.pos=vec2d(2,0);
      b.air=true;
      b.type=VH;
      b.att_cdt=0;
      b.hp=100;
      b.our=false;
      b.end=vec2d(0,0);
    }
    for(;;){
      w.update(*this,1,true);
      int gg=1;
    }
  }
  real sim_time;
  int rs_size;
  vec2d get_wh(){return vec2d(world.width,world.height);}
  #ifdef QAP_LITE_H
    class TGame:public TQapGameV2{
    public:
      t_app*app;
      real scale=3.94;//1.17;
      vec2d cam_pos=vec2d(213,-146);//vec2d(+1,-1)*512;
    public:
      #include "qaplite\QapKbOnDownDoInvFlag.inl"
    public:
      void init(){
        static bool once=false;if(once)return;once=true;
      }
    public:
      static void inv(volatile bool&flag){flag=!flag;}

      vec2d s2w(const vec2d&pos)
      {
        bool offcentric=false; auto cam_dir=vec2d(1,0);
        return t_offcentric_scope::screen_to_world(viewport,pos,cam_pos,cam_dir,scale,offcentric);
      }
      vec2d w2s(const vec2d&pos)
      {
        bool offcentric=false; auto cam_dir=vec2d(1,0);
        return t_offcentric_scope::make_xf(viewport,cam_pos,cam_dir,scale,offcentric)*pos;
      }
      int frame_id=0;int d_frame=1;
      void DoMove()
      {
        QAP_FOREACH(kb_flags,if(kb.OnDown(ex.key))inv(ex.flag));
        if(kb.Down[VK_ESCAPE])win.Close();
        if(kb.Down[VK_ESCAPE]&&kb.Down[VK_SHIFT]){TerminateProcess(GetCurrentProcess(),0);}
        if(kb.Down(VK_ADD))scale*=1.01;
        if(kb.Down(VK_SUBTRACT))scale/=1.01;
        if(kb.Down(VK_DIVIDE)){scale=1.17;cam_pos=vec2d(512,-512);}
        if(kb.OnDown(VK_MULTIPLY))scale/=0.5;
        if(kb.OnDown(VK_SPACE))inv(app->pause);
        {cam_pos+=kb.get_dir_from_wasd_and_arrows()*(10.0/scale);}
        if(kb.OnDown(VK_HOME))frame_id=0;
        if(kb.OnDown(VK_END))frame_id=std::max<int>(0,int(app->replay.size())-1);
        if(kb.OnDown(VK_UP)){d_frame++;d_frame=Clamp<int>(d_frame,-1,+1);}
        if(kb.OnDown(VK_DOWN)){d_frame--;d_frame=Clamp<int>(d_frame,-1,+1);}
        for(int i=0;i<=9;i++)if(kb.OnDown('0'+i))d_frame=Sign(d_frame)*i;
        if(kb.Down(mbRight)){frame_id=app->replay.size()*(mpos.x/viewport.size.x+0.5);}
        //"world.update(...,LEN_KOEF)"
        frame_id+=d_frame;
        frame_id=app->replay.empty()?0:Clamp<int>(frame_id,0,int(app->replay.size())-1);
        //if(kb.OnDown(VK_DOWN))app->lock_step=true;
        if(kb.OnDown(VK_RIGHT)){
          if(frame_id<0)frame_id=int(app->replay.size())-1;
          frame_id++;
          if(frame_id>=app->replay.size()){
            frame_id=-1;
            app->lock_step=true;
          }
          //app->pause=true;
        }
        if(kb.OnDown(VK_LEFT)){
          if(frame_id<0)frame_id=int(app->replay.size())-1;
          frame_id--;
          if(frame_id<0)frame_id=0;
          //app->pause=true;
        }
        auto zK=1.5;
        if(zDelta>0){auto wp=s2w(mpos);scale*=zK;cam_pos+=(w2s(wp)-mpos)*(1.0/scale);}
        if(zDelta<0){auto wp=s2w(mpos);scale/=zK;cam_pos+=(w2s(wp)-mpos)*(1.0/scale);}
        static vec2d drag_wp;
        if(kb.OnDown(mbLeft)){drag_wp=s2w(mpos);}
        if(kb.Down(mbLeft)){cam_pos+=-s2w(mpos)+drag_wp;}
        if(kb.OnDown(VK_F12)){
          //msg="QapSizeOf(app->replay) = "+IToS(QapSizeOf(app->replay));
          //msg=
        }
      }
      void clear(){D9Dev.Clear3D(1?0xffc8c8c8:0xff000000);}
      
      t_app::t_world_log&get_w_empty(){static t_app::t_world_log tmp;return tmp;};
      #define DECLARE(FIELD)auto&FIELD=qap_check_id(app->replay,frame_id)?app->replay[frame_id].FIELD:get_w_empty().FIELD;
      void DoDraw()
      {
        std::lock_guard<std::mutex> guard(app->myMutex);
        D9Dev.Set2D();
    
        D9Dev.pDev->SetRenderState(D3DRS_LIGHTING,false);
        D9Dev.pDev->SetRenderState(D3DRS_ZENABLE,false);
        D9Dev.pDev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
    
        qDev.BindTex(0,nullptr);
        QapDev::BatchScope Scope(qDev);
        {
          t_offcentric_scope scope(qDev,/*obj.pos+*/cam_pos,vec2d(1,0),scale,false);
          render();
        }
        DrawDownedKeys();
        consize=win.GetClientSize();
        int y=0;int dy=16;
        auto add=[&](const string&text){
          y-=dy;
          auto backup_color=qDev.color;
          qDev.color=0xFF000000;
          qap_text::draw(qDev,viewport.get_vertex_by_dir(vec2d(-1,1))+vec2d(16+1,y-1),text,16);
          qDev.color=backup_color;
          qap_text::draw(qDev,viewport.get_vertex_by_dir(vec2d(-1,1))+vec2d(16,y),text,16);
        };
        qDev.color=0xff000000;
        add("app->world.tickIndex = "+IToS(app->world.tickIndex));
        add("frame_id = "+IToS(frame_id));

        auto f=[&](char c,bool enemy){
          DECLARE(w);
          auto vehs=w.get_arr();
          auto t=app->CharToVehicleType(c);
          qDev.color=type2color(t);
          if(enemy)qDev.color=qDev.color.swap_rb();
          int n=0;QAP_FOREACH(vehs,if(ex.type==t&&app->is_our(ex)==!enemy)n++);
          int attready_n=0;QAP_FOREACH(vehs,if(ex.type==t&&app->is_our(ex)==!enemy)if(ex.att_cdt<=0)attready_n++);
          add(string(enemy?"E":"")+"V"+CToS(c)+" = "+IToS(n)+"  //ready = "+IToS(attready_n));
        };
        f('T',false);
        f('I',false);
        f('H',false);
        f('F',false);
        f('A',false);
        f('T',true);
        f('I',true);
        f('H',true);
        f('F',true);
        f('A',true);
        y-=dy;
        add("sim_time = "+FToS(app->sim_time)+" ms");
        add("rs_size = "+IToS(app->rs_size));
        add("sim_time/rs_size = "+FToS(app->sim_time/app->rs_size)+" ms");
        y-=dy;
        if(app->world.players.size())
        {
          DECLARE(op);
          DECLARE(me);
          DECLARE(number_of_groups);
          add("me.score = "+IToS(me.score));
          add("op.score = "+IToS(op.score));
          add("number_of_groups = "+IToS(number_of_groups));
        }
        y-=dy;
        if(QapKbOnDownDoInvFlag("need_print_info",'I',true))
        {
          add("---info---");
          DECLARE(info);
          QAP_FOREACH(info,add(ex));
        }
        add("---other---");
        {
          DECLARE(actionticks);
          DECLARE(actions_per_sec);
          DECLARE(op);
          DECLARE(me);
          DECLARE(w);
          add("actions_ready = "+IToS(how_much_actions_ready_in_next_ticks(actionticks,w.tickIndex,app->ticks_per_sec,actions_per_sec)));
          add("actionticks.size() = "+IToS(actionticks.size()));
          add("actions_per_sec = "+IToS(actions_per_sec));
          add("op.nuke_tick = "+IToS(op.nextNuclearStrikeTickIndex));
          add("me.nuke_tick = "+IToS(me.nextNuclearStrikeTickIndex));
        }
        if(QapKbOnDownDoInvFlag("vehs_under_mouse",'V',true))
        {
          DECLARE(w);
          auto wmp=s2w(mpos);
          auto arr=w.get_arr();
          string types;
          //add("---vehs_under_mouse---");
          for(int i=0;i<arr.size();i++){
            auto&ex=arr[i];
            if(!ex.pos.inv_y().dist_to_point_less_that_r(wmp,w.r))continue;
            types+=app->VehicleTypeToString(ex.type)+"  ";
          }
          add("vehs_types_under_mouse: "+types);
          int gg=1;
        }
        if(QapKbOnDownDoInvFlag("need_print_move_log",'M',true))for(;;)
        {
          add("---replay moves---");
          auto&arr=app->replay;
          if(!arr.size()){add("[...replay empty...]");break;}
          for(int i=0;i<60;i++)
          {
            auto id=(frame_id<0?int(arr.size())-1:frame_id)-i;
            if(!qap_check_id(arr,id))break;
            auto&ex=arr[id];
            auto act=ActionToString(ex.move.action);
            auto veh=VehicleTypeToString(ex.move.vehicleType);
            if(!QapKbOnDownDoInvFlag("show_unk_actions",'U',false))if(ex.move.action==ActionType::_UNKNOWN_)continue;
            add("t:"+IToS(id)+"   "+veh+"   "+act);
          }
          break;
        }
        perf_text_out();
      }
      t_app::t_world&get_sim_w(){
        auto&sim_w=qap_check_id(app->replay,frame_id)?app->replay[frame_id].sim_w:get_w_empty().sim_w;
        if(sim_w.r>0)return sim_w;
        for(int i=frame_id;i>=0;i--){
          if(!qap_check_id(app->replay,i))return get_w_empty().sim_w;
          if(app->replay[i].sim_w.r>0)return app->replay[i].sim_w;
        }
        return get_w_empty().sim_w;
      }
      void render()
      {
        DECLARE(w);
        auto&sim_w=get_sim_w();//DECLARE(sim_w);
        auto fog=QapKbOnDownDoInvFlag("draw_fog_of_war",'O',true)&&app->game.fogOfWarEnabled;
        auto bg_color=0xCCFFFFFF;auto back_color=fog?0xff777777:bg_color;
        qDev.color=back_color;
        qDev.DrawQuad(app->get_wh().inv_y()*0.5,app->get_wh());
        qDev.color=0xFF000000;
        if(fog)
        {
          DECLARE(objs);
          auto arr=w.get_arr();
          auto f=[&](t_unit&ex,int i)
          {
            if(!ex.our)return;
            auto r=app->get_vis_range(ex.type)*app->get_vis_k(ex.pos,ex.air);
            auto p=ex.pos.inv_y();
            {qDev.color=bg_color;qDev.color.a=0xff;qDev.DrawSolidCircle(p,r,32,0);}
          };
          arr.for_each(f);
        }
        if(bool draw_termap=true)
        {
          auto&m=app->termap;auto cs=app->get_wh()*(1.0/m.w);
          for(int y=0;y<m.h;y++)for(int x=0;x<m.w;x++){
            real v=m.get(x,y);
            qDev.color=0x11000000;
            qDev.DrawQuad((cs.Mul(vec2d(x,y))+cs*0.5).inv_y(),cs*v);
          }
        }
        if(bool draw_wetmap=true)
        {
          auto&m=app->wetmap;auto cs=app->get_wh()*(1.0/m.w);
          for(int y=0;y<m.h;y++)for(int x=0;x<m.w;x++){
            real v=1.0-m.get(x,y);
            qDev.color=0x11003333;
            qDev.DrawQuad((cs.Mul(vec2d(x,y))+cs*0.5).inv_y(),cs*v);
            qDev.DrawRectAsQuad((cs.Mul(vec2d(x,y))+cs*0.5).inv_y(),cs,1);
          }
        }
        if(QapKbOnDownDoInvFlag("draw_factorys",'F',true))
        {
          DECLARE(objs);
          DECLARE(op);
          DECLARE(me);
          auto r=app->w.r;
          for(int i=0;i<objs.size();i++)
          {
            auto&ex=objs[i];
            auto p=app->get_pos(ex).inv_y();auto wh=app->get_obj_size();
            qDev.color=0x2F005500;
            qDev.DrawQuad(p,wh);
            qDev.DrawSolidCircle(p,wh.x*0.5,ex.type==FacilityType::CONTROL_CENTER?64:4,0);
            qDev.color=0x8E000000;
            if(ex.ownerPlayerId==me.id)qDev.color=0x8Eff0000;
            int enabled=false;
            if(ex.vehicleType!=VehicleType::_UNKNOWN_){
              qDev.color=type2color(ex.vehicleType);enabled=true;
            }
            if(ex.ownerPlayerId==op.id)qDev.color=qDev.color.swap_rb();
            qDev.DrawRectAsQuad(p,wh,enabled?4:2);//qDev.DrawSolidCircle(p,r,16,0);
            auto points=fabs(ex.capturePoints);
            //if(points==100)continue;
            qDev.color=0xFFFFFF00;
            if(ex.capturePoints<0)qDev.color=qDev.color.swap_rb();
            auto bar_w=wh.x;auto bar_h=r*0.5;auto hp=(points/100.0);//hp=0.8;
            qDev.DrawQuad(p+vec2d((hp-1.0)*0.5*bar_w,+wh.y*0.5),vec2d(bar_w*hp,bar_h));
            qDev.color=0xFF000000;
            qDev.DrawRectAsQuad(p+vec2d(0,+r),vec2d(bar_w,bar_h),0.10);
          }
        }
        if(bool need_draw_vehs=!kb.Down[VK_CONTROL])
        {
          auto arr=w.get_arr();
          if(QapKbOnDownDoInvFlag("draw_attack_r",'R',false))
          {
            for(int k=0;k<2;k++)
            {
              auto f=[&](t_unit&ex,int i)
              {
                auto p=app->get_pos(ex).inv_y();
                auto ar=app->get_air_range(ex.type);
                auto gr=app->get_gnd_range(ex.type);
                //real maxcdt=app->get_att_cdt(ex.type);
                //auto koef=(1.0-ex.att_cdt/maxcdt);
                //ar=ar-ex.att_cdt*app->get_speed(VT)*app->get_speed_factor(TerrainType::SWAMP);
                //gr=gr-ex.att_cdt*app->get_speed(VT)*app->get_speed_factor(TerrainType::SWAMP);
                //ar=std::max(0.0,ar);
                //gr=std::max(0.0,gr);
                if(k==0)if(auto r=std::min(ar,gr)){qDev.color=r==ar?0x10000000:0x1000ff00;qDev.DrawSolidCircle(p,r,16,0);}
                if(k==1)if(auto r=std::max(ar,gr)){qDev.color=r==ar?0x10000000:0x1000ff00;qDev.DrawSolidCircle(p,r,16,0);}
              };
              arr.for_each(f);
            }
          }
          auto f=[&](t_unit&ex,int i)
          {
            auto p=app->get_pos(ex).inv_y();auto r=app->w.r;
            qDev.color=0x20000000;
            qDev.DrawSolidCircle(p,r-1,16,0);//qDev.DrawCircle(p,r,0,1,16);
            qDev.color=type2color(ex.type);
            if(!app->is_our(ex))qDev.color=qDev.color.swap_rb();
            qDev.DrawCircle(p,r-0.5,0,1,16);//qDev.DrawSolidCircle(p,r,16,0);
            if(ex.hp==100)return;
            qDev.color=0xFF00FF00;auto bar_w=r*2;auto bar_h=r*0.5;auto hp=(ex.hp/100.0);//hp=0.8;
            qDev.DrawQuad(p+vec2d((hp-1.0)*0.5*bar_w,+r),vec2d(bar_w*hp,bar_h));
            qDev.color=0xFF000000;
            qDev.DrawRectAsQuad(p+vec2d(0,+r),vec2d(bar_w,bar_h),0.10);
          };
          arr.for_each(f);
        }
        bool need_draw_sim_bars=QapKbOnDownDoInvFlag("draw_sim_w_bars",'B',false);
        if(QapKbOnDownDoInvFlag("draw_sim_w",'H',true))
        {
          auto arr=sim_w.get_arr();
          auto f=[&](t_unit&ex,int i)
          {
            auto p=ex.pos.inv_y();auto r=app->w.r*0.45;auto ls=r*0.5;
            qDev.color=0x80000000;
            qDev.DrawCircle(p,r-0.5*ls,0,ls,16);
            qDev.color=type2color(ex.type);
            if(!ex.our)qDev.color=qDev.color.swap_rb();
            qDev.color.a=0x80;
            qDev.DrawSolidCircle(p,r,16,0);
            if(need_draw_sim_bars)
            {
              if(ex.hp==100)return;
              qDev.color=0xFF00FF00;auto bar_w=r*2;auto bar_h=r*0.5;auto hp=(ex.hp/100.0);//hp=0.8;
              qDev.DrawQuad(p+vec2d((hp-1.0)*0.5*bar_w,+r),vec2d(bar_w*hp,bar_h));
              qDev.color=0xFF000000;
              qDev.DrawRectAsQuad(p+vec2d(0,+r),vec2d(bar_w,bar_h),0.10);
            }
          };
          arr.for_each(f);
          int gg=1;
        }
        if(bool need_draw_nuke=true)
        {
          DECLARE(op);
          DECLARE(me);
          auto tickIndex=frame_id;auto r=app->w.r;
          t_nuclear_explosion na;na.load(me,tickIndex);
          t_nuclear_explosion nb;nb.load(op,tickIndex);
          if(na.host_id>=0)
          {
            qDev.SetColor(0x80FF8040);
            qDev.DrawSolidCircle(na.pos.inv_y(),app->game.tacticalNuclearStrikeRadius,64,0);
            if(auto*phost=w.get_phost(na.host_id))
            {
              qDev.SetColor(0xff000000);
              qDev.DrawSolidCircle(phost->pos.inv_y(),r,3,0);
            }
          }
          if(nb.host_id>=0)
          {
            qDev.SetColor(0x80408080);
            qDev.DrawSolidCircle(nb.pos.inv_y(),app->game.tacticalNuclearStrikeRadius,64,0);
            if(auto*phost=w.get_phost(nb.host_id))
            {
              qDev.SetColor(0xff000000);
              qDev.DrawSolidCircle(phost->pos.inv_y(),r,3,0);
            }
          }
        }
        int gg=1;
      }
      #undef DECLARE
      QapColor type2color(VehicleType type){
        QapColor out=0xff000000;
        auto f=[&](char c,QapColor color){if(app->CharToVehicleType(c)==type)out=color;};
        f('T',0xBBFF0F0F);
        f('I',0xBBFF8000);
        f('H',0xBBFFFF00);
        f('F',0xBBFFCED0);
        f('A',0xBB9E5507);
        return out;
      }
      static string BToS(bool b){return b?"true":"false";}
      void perf_text_out()
      {
        real frames=(app->world.tickIndex+1);
        auto&perf_sys=get_global_perf();
        int textsize=16; int dy=-textsize*1;
        auto p=viewport.get_vertex_by_dir(vec2d(1,1));p.x-=1024;p.y+=dy;
        #define F(MSG)qap_text::draw(qDev,p.x,p.y,MSG,textsize);p.y+=dy;
        qDev.color=0xff000000;
        F("---perf---");
        for(int i=0;i<perf_sys.arr.size();i++)
        {
          auto&ex=perf_sys.arr[i];
          if(!ex.name||!ex.n)continue;
          qDev.color.a=0xff;
          auto name=string(ex.name);
          F(name+" = "+FToS(ex.ms)+"/"+IToS(ex.n)+" = "+FToS(ex.ms/ex.n)+" ; n/frame = "+FToS(ex.n/frames)+" ; ms/frame = "+FToS(ex.ms/frames));
          /*if(ex.n>1)
          {
            F(name+" = "+FToS(ex.ms)+"/"+IToS(ex.n));
          }else{
            if(name=="cd_num"){
              F(name+" = "+IToS(int(ex.ms)));
            }else{
              F(name+" = "+FToS(ex.ms)+" ms");
            }
          }*/
        }
        //for(int pass_id=0;pass_id<2;pass_id++)
        //for(int i=0;i<perf_sys.old.size();i++)
        //{
        //  auto&ex=perf_sys.old[i];
        //  if(0==pass_id)if(ex.old)continue;
        //  if(1==pass_id)if(!ex.old)continue;
        //  qDev.color.a=ex.old?0x80:0xff;
        //  auto name=string(ex.name);
        //  if(ex.n>1)
        //  {
        //    F(name+" = "+FToS(ex.ms)+"/"+IToS(ex.n));
        //  }else{
        //    if(name=="cd_num"){
        //      F(name+" = "+IToS(int(ex.ms)));
        //    }else{
        //      F(name+" = "+FToS(ex.ms)+" ms");
        //    }
        //  }
        //}
        #undef F
      }
    };
    void win_main(t_app*app)
    {
      static GlobalEnv global_env(GetModuleHandle(NULL),0,"",SW_SHOW);
      auto on_heap=make_unique<TGame>();
      TGame&builder=*on_heap;
      builder.app=app;
      builder.init();
      builder.DoNice();
      qap_lite=false;
    }
    #define KB_HANDLER(){\
      if(IsKeyDown(VK_F6))app.run_qap_lite();\
      for(;app.pause&&!app.lock_step;){Sleep(16);}\
      if(app.lock_step){app.lock_step=false;}\
    }
    #define LOCK_GUARD()std::lock_guard<std::mutex> guard(app.myMutex);
    std::mutex myMutex;volatile bool pause=false;volatile bool lock_step=false;volatile bool qap_lite=false;
    void run_qap_lite(){
      if(qap_lite)return;
      if(file_get_contents("run_qaplite.txt")!="YES")return;
      qap_lite=true;
      std::thread render([this](){win_main(this);});
      render.detach();
    }
    static void qap_lite_runner(t_app&app){
      for(;;){
        Sleep(16);if(IsKeyDown(VK_F6))app.run_qap_lite();
      }
    }
    t_app(){
      run_qap_lite();
      std::thread qap_lite_runner_thread([this](){qap_lite_runner(*this);});
      qap_lite_runner_thread.detach();
    }
  #else
  #define KB_HANDLER()
  #define LOCK_GUARD()
  #endif
};
#ifdef AUTO_CRASH
#define CRASH_HANDLER()QAP_FOREACH(world.players,if(ex.strategyCrashed)exit(31456));
#else
void CRASH_HANDLER(){};
#endif
static t_app app;

void MyStrategy::move(const Player&me,const World&world,const Game&game,Move&move){
  CRASH_HANDLER();
  KB_HANDLER();
  {
    app.objs=world.facilities;
    app.op=world.getOpponentPlayer();
    app.me=me;app.world=world;app.game=game;app.move=move;
    app.update(world);
  }
  app.before_move();
  {
    LOCK_GUARD();
    app.record();
  }
  QAP_PERF_CODE(app.do_move());
  app.after_move();
  move=app.move;
}

MyStrategy::MyStrategy() { }
