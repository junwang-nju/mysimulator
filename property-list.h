
#ifndef _Property_List_H_
#define _Property_List_H_

#include "monomer.h"
#include "fix-vector.h"

namespace std {

  class PropertyList : public varVector<Property> {

    public:

      typedef PropertyList          Type;
      typedef varVector<Property>   ParentType;

      varVector<uint>   gInfo;
      varVector<double> gCoordinate;
      varVector<double> gVelocity;
      varVector<double> gGradient;
      varVector<uint>   gMask;
      varVector<double> gDMask;
      varVector<double> gMass;
      varVector<double> gIMass;
      varVector<double> gInCoordinate;
      varVector<double> gInVelocity;
      varVector<double> gInGradient;

      PropertyList() : ParentType(), gInfo(), gCoordinate(), gVelocity(),
                       gMask(), gDMask(), gMass(), gIMass(), gInCoordinate(),
                       gInVelocity(), gInGradient() {}

      Type& gAllocate(const VectorBase<uint>& MerTypeList,
                      const VectorBase<uint>& MerFlag, const uint& Dim) {
        fixVector<uint,NumberPropertyFeatures> num;
        varVector<fixVector<uint,NumberPropertyFeatures> > offset,size; 
        uint n,m;
        n=MerTypeList.size();
        this->allocate(n);
        offset.allocate(n);
        size.allocate(n);
        num=0U;
        offset[0]=0U;
        for(uint i=0;i<n;++i) {
          if(i>0) offset[i]+=size[i-1];
          size[i]=0U;
          if(MerTypeList[i]==Particle) {
            m=MerFlag[i];
            size[i][property_info]=particle_info_size;
            size[i][property_coordinate]=Dim;
            size[i][property_mask]=Dim;
            size[i][property_dmask]=Dim;
            if(m&VelocityEnable) size[i][property_velocity]=Dim;
            if(m&GradientEnable) size[i][property_gradient]=Dim;
            if(m&MassEnable) {
              size[i][property_mass]=particle_mass_size;
              size[i][property_imass]=particle_imass_size;
            }
            for(uint k=0;k<NumberPropertyFeatures;++k)  num[k]+=size[i][k];
          } else { myError("Unknown Monomer Type!"); }
        }
        if(num[property_info])
            gInfo.allocate(num[property_info]);
        if(num[property_coordinate])
            gCoordinate.allocate(num[property_coordinate]);
        if(num[property_mask])
            gMask.allocate(num[property_mask]);
        if(num[property_dmask])
            gDMask.allocate(num[property_dmask]);
        if(num[property_velocity])
            gVelocity.allocate(num[property_velocity]);
        if(num[property_gradient])
            gGradient.allocate(num[property_gradient]);
        if(num[property_mass])
            gMass.allocate(num[property_mass]);
        if(num[property_imass])
            gIMass.allocate(num[property_imass]);
        if(num[property_icoordinate])
            gInCoordinate.allocate(num[property_icoordinate]);
        if(num[property_ivelocity])
            gInVelocity.allocate(num[property_ivelocity]);
        if(num[property_igradient])
            gInGradient.allocate(num[property_igradient]);
        Property* nowProp;
        for(uint i=0;i<n;++i) {
          nowProp=&(this->operator[](i));
          if(size[i][property_info])
            nowProp->Info.refer(gInfo,offset[i][property_info],
                                      size[i][property_info]);
          if(size[i][property_coordinate])
            nowProp->Coordinate.refer(gCoordinate,
                                      offset[i][property_coordinate],
                                      size[i][property_coordinate]);
          if(size[i][property_mask])
            nowProp->Mask.refer(gMask,offset[i][property_mask],
                                      size[i][property_mask]);
          if(size[i][property_mask])
            nowProp->DMask.refer(gDMask,offset[i][property_dmask],
                                        size[i][property_dmask]);
          if(size[i][property_velocity])
            nowProp->Velocity.refer(gVelocity,offset[i][property_velocity],
                                              size[i][property_velocity]);
          if(size[i][property_gradient])
            nowProp->Gradient.refer(gGradient,offset[i][property_gradient],
                                              size[i][property_gradient]);
          if(size[i][property_ivelocity])
            nowProp->internalVelocity.refer(gInVelocity,
                                            offset[i][property_ivelocity],
                                            size[i][property_ivelocity]);
          if(size[i][property_igradient])
            nowProp->internalGradient.refer(gInGradient,
                                            offset[i][property_igradient],
                                            size[i][property_igradient]);
          if(size[i][property_mass])
            nowProp->Mass.refer(gMass,offset[i][property_mass],
                                      size[i][property_mass]);
          if(size[i][property_imass])
            nowProp->IMass.refer(gIMass,offset[i][property_imass],
                                        size[i][property_imass]);
        }
        for(uint i=0;i<n;++i) {
          this->operator[](i).Info[MonomerTypeID]=MerTypeList[i];
          this->operator[](i).Info[MonomerDimension]=Dim;
        }
        return *this;
      }

  };

}

#endif

