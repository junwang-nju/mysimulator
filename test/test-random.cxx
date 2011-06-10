
#include "random/mt-standard/allocate.h"
#include "random/mt-standard/io.h"
#include "random/mt-standard/copy.h"
#include "random/mt-sfmt/allocate.h"
#include "random/mt-sfmt/io.h"
#include "random/mt-sfmt/copy.h"
#include "random/mt-dsfmt/allocate.h"
#include "random/mt-dsfmt/io.h"
#include "random/mt-dsfmt/copy.h"
#include "random/box-muller/allocate.h"
#include "random/box-muller/io.h"
#include "random/box-muller/copy.h"
#include "vector/allocate.h"
#include "vector/fill.h"
#include "io/input/string/interface.h"
#include "io/output/string/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  cout<<endl;
  MT_Standard G,G1;
  cout<<"Before Allocation: Flag of Generator is\t"<<G.sl<<endl;
  allocate(G);
  cout<<"After Allocation: Flag of Generator is\t"<<G.sl<<endl;
  imprint(G1,G);
  cout<<"After Imprint: Flag of Generator is\t"<<G1.sl<<endl;
  release(G1);
  cout<<"After Release: Flag of Generator is\t"<<G1.sl<<endl;

  cout<<endl;
  cout<<"Output after default Allocation:\t";
  cout<<G.rand<unsigned int>()<<endl;
  G.init(328472);
  cout<<"Output after manual Initiation:\t";
  cout<<G.rand<unsigned int>()<<endl;
  G.initWithTime();
  cout<<"Output after Initiation with Time:\t";
  cout<<G.rand<unsigned int>()<<endl;

  cout<<endl;
  cout<<"double rand in region [0,1]:\t";
  cout<<G.doubleClose0Close1()<<endl;
  cout<<"double rand in region [0,1):\t";
  cout<<G.doubleClose0Open1()<<endl;
  cout<<"double rand in region (0,1):\t";
  cout<<G.doubleOpen0Open1()<<endl;
  cout<<"53-bit double rand in region [0,1) (Slow Version):\t";
  cout<<G.double53bitSlow()<<endl;
  cout<<"63-bit double rand in region [0,1) (Slow Version):\t";
  cout<<G.longdouble63bitSlow()<<endl;
  cout<<"Default double generator in region [0,1):\t";
  cout<<G.randomDouble()<<endl;
  cout<<"Default unsigned int generator in region [0,1):\t";
  cout<<G.randomUnsignedInt()<<endl;
  cout<<"rand method for double:\t";
  cout<<G.rand<double>()<<endl;
  cout<<"rand method for unsigned int:\t";
  cout<<G.rand<unsigned int>()<<endl;
  cout<<"rand method for int:\t";
  cout<<G.rand<int>()<<endl;

  cout<<endl;
  const unsigned int n=1000000;
  Vector<double> v(n);
  G.fill(v);
  cout<<"Last element after fill with MT_Standard generator:\t";
  cout<<v[n-1]<<endl;
  Vector<unsigned int> hist(1001);
  fill(hist,0U);
  for(unsigned int i=0;i<n;++i) hist[static_cast<unsigned int>(v[i]*1000)]++;
  cout<<"histogram of the output double random numbers:"<<endl;
  for(unsigned int i=0;i<=1000;++i) cout<<i<<"\t"<<hist[i]<<endl;
  cout<<"Correlation check for mt-standard:"<<endl;
  allocate(hist,10000);
  fill(hist,0U);
  for(unsigned int i=1;i<n;++i)
    hist[static_cast<unsigned int>(v[i-1]*100)*100+static_cast<unsigned int>(v[i]*100)]++;
  for(unsigned int i=0;i<hist.size;++i) cout<<i<<"\t"<<hist[i]<<endl;

  cout<<endl;
  const unsigned int Nbuff=409600;
  const unsigned int Ncmp=100;
  char buff[Nbuff];
  StringInput SI(buff,Nbuff);
  StringOutput SO(buff,Nbuff);
  Vector<unsigned int> vbf(Ncmp),vft(Ncmp);
  SO<<G;
  G.fill(vbf);
  SI>>G;
  G.fill(vft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(vbf[i]!=vft[i])  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  allocate(G1);
  copy(G1,G);
  G.fill(vbf);
  G1.fill(vft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(vbf[i]!=vft[i])  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  MT_SFMT<> GS,GS1;
  cout<<"Before Allocation: Flag of Generator is\t"<<GS.idx<<endl;
  allocate(GS);
  cout<<"After Allocation: Flag of Generator is\t"<<GS.idx<<endl;
  imprint(GS1,GS);
  cout<<"After Imprint: Flag of Generator is\t"<<GS1.idx<<endl;
  release(GS1);
  cout<<"After Release: Flag of Generator is\t"<<GS1.idx<<endl;

  cout<<endl;
  cout<<"Output after default Allocation:\t";
  cout<<GS.rand<unsigned int>()<<endl;
  GS.init(328472);
  cout<<"Output after manual Initiation:\t";
  cout<<GS.rand<unsigned int>()<<endl;
  GS.initWithTime();
  cout<<"Output after Initiation with Time:\t";
  cout<<GS.rand<unsigned int>()<<endl;
  Vector<unsigned int> vi(100);
  for(unsigned int i=0;i<100;i++) vi[i]=G.rand<unsigned int>();
  GS.init(vi);
  cout<<"Output after Initiation with Array:\t";
  cout<<GS.rand<unsigned int>()<<endl;

  cout<<endl;
  cout<<"double rand in region [0,1]:\t";
  cout<<GS.doubleClose0Close1()<<endl;
  cout<<"double rand in region [0,1):\t";
  cout<<GS.doubleClose0Open1()<<endl;
  cout<<"double rand in region (0,1):\t";
  cout<<GS.doubleOpen0Open1()<<endl;
  cout<<"53-bit double rand in region [0,1) (Slow Version):\t";
  cout<<GS.double53bitSlow()<<endl;
  cout<<"63-bit double rand in region [0,1) (Slow Version):\t";
  cout<<GS.longdouble63bitSlow()<<endl;
  cout<<"Default double generator in region [0,1):\t";
  cout<<GS.randomDouble()<<endl;
  cout<<"Default unsigned int generator in region [0,1):\t";
  cout<<GS.randomUnsignedInt()<<endl;
  cout<<"rand method for double:\t";
  cout<<GS.rand<double>()<<endl;
  cout<<"rand method for unsigned int:\t";
  cout<<GS.rand<unsigned int>()<<endl;
  cout<<"rand method for long double:\t";
  cout<<GS.rand<long double>()<<endl;
  cout<<"rand method for int:\t";
  cout<<GS.rand<unsigned long long>()<<endl;

  cout<<endl;
  while(GS.idx!=GS.N32) GS.rand<unsigned int>();
  allocate(vi,n);
  GS.fillFast(vi);
  allocate(v,n);
  GS.fill(v);
  cout<<"Last element after fill with MT_SFMT generator:\t";
  cout<<v[n-1]<<endl;
  allocate(hist,1001);
  fill(hist,0U);
  for(unsigned int i=0;i<n;++i) hist[static_cast<unsigned int>(v[i]*1000)]++;
  cout<<"histogram of the output double random numbers:"<<endl;
  for(unsigned int i=0;i<=1000;++i) cout<<i<<"\t"<<hist[i]<<endl;
  cout<<"Correlation check for mt-sfmt:"<<endl;
  allocate(hist,10000);
  fill(hist,0U);
  for(unsigned int i=1;i<n;++i)
    hist[static_cast<unsigned int>(v[i-1]*100)*100+static_cast<unsigned int>(v[i]*100)]++;
  for(unsigned int i=0;i<hist.size;++i) cout<<i<<"\t"<<hist[i]<<endl;

  cout<<endl;
  SO<<GS;
  GS.fill(vbf);
  SI>>GS;
  GS.fill(vft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(vbf[i]!=vft[i])  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  allocate(GS1);
  copy(GS1,GS);
  GS.fill(vbf);
  GS1.fill(vft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(vbf[i]!=vft[i])  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  MT_dSFMT<> GD,GD1;
  cout<<"Before Allocation: Flag of Generator is\t"<<GD.idx<<endl;
  allocate(GD);
  cout<<"After Allocation: Flag of Generator is\t"<<GD.idx<<endl;
  imprint(GD1,GD);
  cout<<"After Imprint: Flag of Generator is\t"<<GD1.idx<<endl;
  release(GD1);
  cout<<"After Release: Flag of Generator is\t"<<GD1.idx<<endl;

  cout<<endl;
  cout<<"Output after default Allocation:\t";
  cout<<GD.rand<unsigned int>()<<endl;
  GD.init(328472);
  cout<<"Output after manual Initiation:\t";
  cout<<GD.rand<unsigned int>()<<endl;
  GD.initWithTime();
  cout<<"Output after Initiation with Time:\t";
  cout<<GD.rand<unsigned int>()<<endl;
  for(unsigned int i=0;i<100;i++) vi[i]=G.rand<unsigned int>();
  GD.init(vi);
  cout<<"Output after Initiation with Array:\t";
  cout<<GD.rand<unsigned int>()<<endl;

  cout<<endl;
  cout<<"double rand in region [1,2):\t";
  cout<<GD.doubleClose1Open2()<<endl;
  cout<<"double rand in region (0,1]:\t";
  cout<<GD.doubleOpen0Close1()<<endl;
  cout<<"double rand in region (0,1):\t";
  cout<<GD.doubleOpen0Open1()<<endl;
  cout<<"Default double generator in region [0,1):\t";
  cout<<GD.randomDouble()<<endl;
  cout<<"Default unsigned int generator in region [0,1):\t";
  cout<<GD.randomUnsignedInt()<<endl;
  cout<<"rand method for double:\t";
  cout<<GD.rand<double>()<<endl;
  cout<<"rand method for unsigned int:\t";
  cout<<GD.rand<unsigned int>()<<endl;

  cout<<endl;
  allocate(vi,n);
  GD.fill(vi);
  allocate(v,n);
  GD.fillFast(v);
  GD.fillFastClose1Open2(v);
  GD.fillFastOpen0Close1(v);
  GD.fillFastOpen0Open1(v);
  GD.fill(v);
  cout<<"Last element after fill with MT_dSFMT generator:\t";
  cout<<v[n-1]<<endl;
  allocate(hist,1001);
  fill(hist,0U);
  for(unsigned int i=0;i<n;++i) hist[static_cast<unsigned int>(v[i]*1000)]++;
  cout<<"histogram of the output double random numbers:"<<endl;
  for(unsigned int i=0;i<=1000;++i) cout<<i<<"\t"<<hist[i]<<endl;
  cout<<"Correlation check for mt-dsfmt:"<<endl;
  allocate(hist,10000);
  fill(hist,0U);
  for(unsigned int i=1;i<n;++i)
    hist[static_cast<unsigned int>(v[i-1]*100)*100+static_cast<unsigned int>(v[i]*100)]++;
  for(unsigned int i=0;i<hist.size;++i) cout<<i<<"\t"<<hist[i]<<endl;

  cout<<endl;
  SO<<GD;
  GD.fill(vbf);
  SI>>GD;
  GD.fill(vft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(vbf[i]!=vft[i])  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  allocate(GD1);
  copy(GD1,GD);
  GD.fill(vbf);
  GD1.fill(vft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(vbf[i]!=vft[i])  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  BoxMuller<MT_dSFMT<> > GB,GB1;
  cout<<"Before Allocation: Flag of Generator is\t"<<GB.isSecond<<endl;
  allocate(GB);
  cout<<"After Allocation: Flag of Generator is\t"<<GB.isSecond<<endl;
  imprint(GB1,GB);
  cout<<"After Imprint: Flag of Generator is\t"<<GB1.isSecond<<endl;
  release(GB1);
  cout<<"After Release: Flag of Generator is\t"<<GB1.isSecond<<endl;

  cout<<endl;
  cout<<"Output after default Allocation:\t";
  cout<<GB.randomDouble()<<endl;
  GB.init(328472);
  cout<<"Output after manual Initiation:\t";
  cout<<GB.randomDouble()<<endl;
  GB.initWithTime();
  cout<<"Output after Initiation with Time:\t";
  cout<<GB.randomDouble()<<endl;
  allocate(vi,100);
  for(unsigned int i=0;i<100;i++) vi[i]=G.rand<unsigned int>();
  GB.init(vi);
  cout<<"Output after Initiation with Array:\t";
  cout<<GB.randomDouble()<<endl;

  cout<<endl;
  cout<<"double rand of Gaussian Distribution:\t";
  cout<<GB.randomDouble()<<endl;

  cout<<endl;
  allocate(v,n*10);
  GB.fill(v);
  cout<<"Last element after fill with Box-Muller generator:\t";
  cout<<v[n-1]<<endl;
  allocate(hist,10001);
  fill(hist,0U);
  for(unsigned int i=0,m;i<n;++i) {
    m=static_cast<unsigned int>(v[i]*1000+5000.5);
    if((m>=0)&&(m<=10000)) hist[m]++;
  }
  cout<<"histogram of the output double random numbers:"<<endl;
  for(unsigned int i=0;i<=10000;++i) cout<<(i-5000.)*1e-3<<"\t"<<hist[i]<<endl;

  cout<<endl;
  Vector<double> dvbf,dvft;
  allocate(dvbf,Ncmp);
  allocate(dvft,Ncmp);
  SO<<GB;
  GB.fill(dvbf);
  SI>>GB;
  GB.fill(dvft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(fabs(vbf[i]-vft[i])>1e-8)  cout<<i<<"\tNot Equal!"<<endl;

  cout<<endl;
  allocate(GB1);
  copy(GB1,GB);
  GB.fill(dvbf);
  GB1.fill(dvft);
  for(unsigned int i=0;i<Ncmp;++i)
    if(fabs(vbf[i]-vft[i])>1e-8)  cout<<i<<"\tNot Equal!"<<endl;

  return 0;
}

