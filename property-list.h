
#ifndef _Property_List_H_
#define _Property_List_H_

#include "var-vector.h"
#include "ref-vector.h"

namespace std {

	template <template <typename> class ListType=varVector,
            template <typename> class PropertyType=refVector,
            typename DataType=double>
	class PropertyList : public ListType<PropertyType<DataType> >{
    public:
      typedef PropertyList<ListType,PropertyType,DataType>  Type;
      typedef ListType<PropertyType<DataType> >             ParentType;
      typedef PropertyType<DataType>                        Property;
      varVector<DataType> PropertyData;

      PropertyList() : ParentType(), PropertyData() {}
      PropertyList(const Type& PL) {
        myError("copier for property list is prohibited!");
      }
      
      Type& BuildStructure(const VectorBase<uint>& ShapeOffset,
                           const VectorBase<uint>& ShapeSize) {
        uint n=ShapeSize.size();
        assert(this->size()==n);
        assert(ShapeOffset.size()==n);
        uint num=ShapeOffset[n-1]+ShapeSize[n-1];
        PropertyData.allocate(num);
        for(uint i=0;i<n;++i)
          this->operator[](i).refer(PropertyData,ShapeOffset[i],ShapeSize[i]);
      	return *this;
      }
      void swap(Type& PL) {
        static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(PL));
        PropertyData.swap(PL.PropertyData);
      }

      Type& operator=(const Type& vb) { return assign(vb); }

      template <typename inputT>
      Type& operator=(const inputT& v) { return assign(v); }

      template <typename inputT>
      Type& operator*=(const inputT& v) { return scale(v); }

      template <typename inputT>
      Type& operator+=(const inputT& v) { return shift(v); }

      Type& assign(const DataType* v, long ncopy, int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const VectorBase<DataType>& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(v,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const Type& v, long ncopy,
                   int voffset=iZero, long vstep=lOne,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(v.PropertyData,ncopy,voffset,vstep,offset,step);
        return *this;
      }

      Type& assign(const VectorBase<DataType>& v) {
        PropertyData.assign(v);
        return *this;
      }

      Type& assign(const Type& v) {
        PropertyData.assign(v.PropertyData);
        return *this;
      }

      Type& assign(const DataType& value, long ncopy,
                   int offset=iZero, long step=lOne) {
        PropertyData.assign(value,ncopy,offset,step);
        return *this;
      }
      
      Type& assign(const DataType& value) {
        PropertyData.assign(value);
        return *this;
      }

      Type& scale(const DataType* v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const DataType& d, long nscale,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(d,nscale,offset,step);
        return *this;
      }

      Type& scale(const DataType& d) {
        PropertyData.scale(d);
        return *this;
      }

      Type& scale(const VectorBase<DataType>& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const Type& v, long nscale,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.scale(v.PropertyData,nscale,voffset,vstep,offset,step);
        return *this;
      }

      Type& scale(const VectorBase<DataType>& v) {
        PropertyData.scale(v);
        return *this;
      }

      Type& scale(const Type& v) {
        PropertyData.scale(v.PropertyData);
        return *this;
      }

      template <typename ScaleT>
      Type& shift(const ScaleT& sv, const DataType* v, long nshift,
                  int soffset=iZero, long sstep=lOne,
                  int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(sv,v,nshift,soffset,sstep,voffset,vstep,
                           offset,step);
        return *this;
      }

      Type& shift(const DataType& value, const VectorBase<DataType>& v,
                  long nshift, int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(value,v,nshift,voffset,vstep,offset,step);
        return *this;
      }
      
      Type& shift(const DataType& value, const Type& v,
                  long nshift, int voffset=iZero, long vstep=lOne,
                  int offset=iZero, long step=lOne) {
        PropertyData.shift(value,v,PropertyData,nshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      Type& shift(const DataType& value, const VectorBase<DataType>& v) {
        PropertyData.shift(value,v);
        return *this;
      }

      Type& shift(const DataType& value, const Type& v) {
        PropertyData.shift(value,v.PropertyData);
        return *this;
      }
      
      template <typename vType>
      Type& shift(const pair<const DataType&,const vType&>& sp) {
        return shift(sp.first,sp.second);
      }

      template <typename vType>
      Type& shift(const pair<const vType&,const DataType&>& sp) {
        return shift(sp.second,sp.first);
      }

      Type& shift(const DataType& value, int offset=iZero, long step=lOne) {
        PropertyData.shift(value,offset,step);
        return *this;
      }

      Type& shift(const VectorBase<DataType>& v) { return shift(dOne,v); }

      Type& shift(const Type& v) { return shift(dOne,v); }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const vTypeA& ShiftFv, const vTypeB& v) {
        return shift(dOne,ShiftFv,v);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const pair<const vTypeA&,const vTypeB&>& sp) {
        return shift(sp.first,sp.second);
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(const DataType& ShiftF,
                  const vTypeA& ShiftFv, const vTypeB& v) {
        PropertyData.scaleshift(dOne,ShiftF,ShiftFv,v);
        return *this;
      }

      template <typename vTypeA, typename vTypeB>
      Type& shift(
          const tr1::tuple<const DataType&,const vTypeA&,const vTypeB&>& st){
        return shift(tr1::get<0>(st),tr1::get<1>(st),tr1::get<2>(st));
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const DataType* ShiftFv, const DataType* v,
                       long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v,nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const VectorBase<DataType>& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v,nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const Type& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v.PropertyData,
                                nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv,
                       const VectorBase<DataType>& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv.PropertyData,v,
                                nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv,const Type& v,long nscaleshift,
                       int sfoffset=iZero, long sfstep=lOne,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        PropertyData.scaleshift(ScaleF,ShiftF,
                                ShiftFv.PropertyData,v.PropertyData,
                                nscaleshift,
                                sfoffset,sfstep,voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv, const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,
                                ShiftFv.PropertyData,v.PropertyData);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv, const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v.PropertyData);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& ShiftFv, const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv.PropertyData,v);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& ShiftFv,
                       const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,ShiftFv,v);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        PropertyData.shift(ShiftF,v,nscaleshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& v, long nscaleshift,
                       int voffset=iZero, long vstep=lOne,
                       int offset=iZero, long step=lOne) {
        scale(ScaleF,nscaleshift,offset,step);
        PropertyData.shift(ShiftF,v.PropertyData,nscaleshift,
                           voffset,vstep,offset,step);
        return *this;
      }
      
      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const VectorBase<DataType>& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,v);
        return *this;
      }

      Type& scaleshift(const DataType& ScaleF, const DataType& ShiftF,
                       const Type& v) {
        PropertyData.scaleshift(ScaleF,ShiftF,v.PropertyData);
        return *this;
      }

  };

  void Activate(VectorBase<uint>& MaskObj) { MaskObj=1; }

  void DeActivate(VectorBase<uint>& MaskObj) { MaskObj=0; }

  void Activate(VectorBase<uint>& MaskObj, const uint& I) { MaskObj[I]=1; }

  void DeActivate(VectorBase<uint>& MaskObj, const uint& I) { MaskObj[I]=0; }

  void Activate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj) {
    MaskObj=1;  DMaskObj=1.;
  }

  void DeActivate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj) {
    MaskObj=0;  DMaskObj=0.;
  }

  void Activate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj,
                const uint& I) {
    MaskObj[I]=1;  DMaskObj[I]=1.;
  }

  void DeActivate(VectorBase<uint>& MaskObj, VectorBase<double>& DMaskObj,
                  const uint& I) {
    MaskObj[I]=0;  DMaskObj[I]=0.;
  }
}

#endif

