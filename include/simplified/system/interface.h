
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/kind/name.h"
#include "system/interaction/interface.h"
#include "force-field/interface.h"
#include "pdb/interface.h"
#include <cstdarg>

namespace mysimulator {

  template <typename GT,unsigned int DIM=GT::Dimension>
  class System {

    public:

      typedef System<GT,DIM>  Type;
      static const ArrayKernelName _VForm = __system_vec_type<DIM>::NAME;

//    private:

      Array<SystemKindName> _kind;
      Array2D<Double,ArrayKernelName::SSE,_VForm>  _X;
      Array2D<Double,ArrayKernelName::SSE,_VForm>  _V;
      Array2D<Double,ArrayKernelName::SSE,_VForm> _G;
      access_ptr<double> _E;
      Array<SystemInteraction<GT,DIM>>  _Interaction;
      Array2D<UInt>  _IGroup;

    public:

      System() : _kind(), _X(), _V(), _G(), _E(), _Interaction(), _IGroup() {}
      System(const Type& S) : System() { imprint(S); operator=(S); }
      System(Type&& S) : System() { swap(S); }
      ~System() { reset(); }

      operator bool() const {
        return (bool)_kind && (bool)_X && (bool)_V && (bool)_G &&
               (bool)_Interaction && (bool)_IGroup;
      }
      void reset() {
        _IGroup.reset();
        _Interaction.reset();
        _E.reset();
        _G.reset();
        _V.reset();
        _X.reset();
        _kind.reset();
      }

      void allocate(ForceField const& FF, ...) {
        reset();
        va_list vl;
        va_start(vl,FF);
        switch(FF.Name()) {
          case ForceFieldName::ResidueGo:
            const char* pdbfile=va_arg(vl,char*);
            PDB F;
            F<<pdbfile;
            unsigned int n=0;
            for(unsigned int i=0;i<F[0].size();++i) n+=F[0][i].size();
            _kind.allocate(n);
            _X.allocate(n,DIM);
            _V.allocate(n,DIM);
            _G.allocate(n,DIM);
            _E.reset(new double,__delete_unit<double>);
            Contact C;
            char* field=nullptr;
            __parse_item_for_forcefield_value(field,FF["ContactMode"].Value(),0);
            if(strcmp(field,"CAlphaDistance")==0) {
              ContactMethod<ContactMethodName::CAlphaDistance> M;
              __delete_array<char>(field);  field=nullptr;
              M.SetThreshold(
                  atof(__parse_item_for_forcefield_value(
                          field,FF["ContactMode"].Value(),3)));
              __delete_array<char>(field);  field=nullptr;
              __parse_item_for_forcefield_value(field,FF["ContactMode"].Value(),1);
              if(strcmp(field,"FirstModel")==0)
                M.SetModelMode(ModelSelectorName::First);
              __delete_array<char>(field);  field=nullptr;
              __parse_item_for_forcefield_value(field,FF["ContactMode"].Value(),2);
              if(strcmp(field,"DefaultAtom")==0)
                M.SetAltMode(AltSelectorName::Default);
              __delete_array<char>(field);  field=nullptr;
              C=F&M;
            }
            F.reset();
            break;
          default:
            fprintf(stderr,"Unknown Force Field Name!\n");
        }
        va_end(vl);
      }

      void swap(Type& S) {
        std::swap(_kind,S._kind);
        std::swap(_X,S._X);
        std::swap(_V,S._V);
        std::swap(_G,S._G);
        std::swap(_E,S._E);
        std::swap(_Interaction,S._Interaction);
        std::swap(_IGroup,S._IGroup);
      }

  };

}

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  void swap(mysimulator::System<GT,DIM>& S1,mysimulator::System<GT,DIM>& S2) {
    S1.swap(S2);
  }

}

#endif

