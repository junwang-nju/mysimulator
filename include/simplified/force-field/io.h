
#ifndef _Force_Field_IO_H_
#define _Force_Field_IO_H_

#include "force-field/interface.h"

namespace mysimulator {

  ForceField& operator<<(ForceField& FF,const char* ffcode) {
    unsigned int n=strlen(ffcode),m;
    char* fname=new char[n+1];
    m=n;
    for(unsigned int i=0;i<n;++i) if(ffcode[i]==':')  { m=i; break; }
    unsigned int bg,ed,cbg;
    if(m<n) {
      for(unsigned int i=m+1;i<n;++i) if(!isspace(ffcode[i])) { bg=i; break; }
      for(unsigned int i=n-1;i>m;--i) if(!isspace(ffcode[i])) { ed=i; break; }
      SubString(fname,ffcode,bg,ed);
      cbg=ed-bg+1;
      if(fname[cbg-1]!='/') { fname[cbg]='/'; ++cbg; }
    } else {
      strncpy(fname,"./",2);
      cbg=2;
    }
    for(unsigned int i=0;i<m-1;++i)  if(!isspace(ffcode[i])) { bg=i; break; }
    for(unsigned int i=m-1;i>=0;--i) if(!isspace(ffcode[i])) { ed=i; break; }
    SubString(fname+cbg,ffcode,bg,ed);
    FILE *fi=nullptr;
    fi=fopen(fname,"rt");
    if(fi==nullptr) fprintf(stderr,"Force Field File %s Not Found!\n",fname);
    else {
      n=0;
      while(fgetc(fi)!=EOF) ++n;
      fclose(fi);
      char *content=new char[n+1];
      fi=fopen(fname,"rt");
      n=0;
      while((content[n++]=fgetc(fi))!=EOF) {}
      content[n-1]='\0';
      fclose(fi);
      if(!((bool)FF)) FF.allocate(__parse_name_for_forcefield(content));
      FF=content;
      __delete_array<char>(content);
    }
    __delete_array<char>(fname);  fname=nullptr;
  }

}

#endif

