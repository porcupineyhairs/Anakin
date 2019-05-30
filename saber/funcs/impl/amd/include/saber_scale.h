/* Copyright (c) 2019 Anakin Authors, Inc. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef ANAKIN_SABER_FUNCS_IMPL_AMD_SABER_SCALE_H
#define ANAKIN_SABER_FUNCS_IMPL_AMD_SABER_SCALE_H
#include "saber/funcs/impl/impl_scale.h"
#include "saber/funcs/base.h"
#include "saber/core/impl/amd/utils/amd_base.h"
#include "saber/saber_types.h"
#include "saber/funcs/impl/impl_base.h"
#include "saber/saber_funcs_param.h"
#include "saber/core/impl/amd/utils/amd_kernel.h"

namespace anakin {

namespace saber {

template <DataType OpDtype>
class SaberScale<AMD, OpDtype> : public ImplBase<AMD, OpDtype, ScaleParam<AMD>> {
public:
    typedef TargetWrapper<AMD> API;
    typedef typename DataTrait<AMD, OpDtype>::Dtype OpDataType;
    typedef AMD_API::TPtr PtrDtype;

    SaberScale()
        : _axis(0)
        , _num_axes(0)
        , _bias_term(false)
        , _inner_dim(0)
        , _scale_dim(0)
    {}

    ~SaberScale() {}

    virtual SaberStatus
    init(const std::vector<Tensor<AMD>*>& inputs,
         std::vector<Tensor<AMD>*>& outputs,
         ScaleParam<AMD>& param,
         Context<AMD>& ctx);

    virtual SaberStatus
    create(const std::vector<Tensor<AMD>*>& inputs,
           std::vector<Tensor<AMD>*>& outputs,
           ScaleParam<AMD>& param,
           Context<AMD>& ctx);

    virtual SaberStatus dispatch(
            const std::vector<Tensor<AMD>*>& inputs,
            std::vector<Tensor<AMD>*>& outputs,
            ScaleParam<AMD>& param);

private:
    int _axis;
    int _num_axes;
    bool _bias_term;
    int _inner_dim;
    int _scale_dim;
    Tensor<AMD> _weight;
    Tensor<AMD> _bias;

    AMDKernelPtr _kernel_Scale_singleBias;
    AMDKernelPtr _kernel_Scale_multiBias;
};
template class SaberScale<AMD, AK_FLOAT>;
} // namespace saber
} // namespace anakin
#endif // ANAKIN_SABER_FUNCS_IMPL_AMD_SABER_SCALE_H
