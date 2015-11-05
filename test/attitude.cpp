#include <cassert>
#include <cstdio>

#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "matrix.hpp"

using namespace matrix;

template class Quaternion<float>;
template class Euler<float>;
template class Dcm<float>;

int main()
{
    double eps = 1e-6;

    // check data
    Eulerf euler_check(0.1f, 0.2f, 0.3f);
    Quatf q_check(0.98334744f, 0.0342708f, 0.10602051f, .14357218f);
    float dcm_data[] =  {
        0.93629336f, -0.27509585f,  0.21835066f,
        0.28962948f,  0.95642509f, -0.03695701f,
        -0.19866933f,  0.0978434f,  0.97517033f
    };
    Dcmf dcm_check(dcm_data);

    // euler ctor
    euler_check.T().print();
    assert((euler_check - Vector3f(0.1f, 0.2f, 0.3f)).norm() < eps);

    // quaternion ctor
    Quatf q(1, 2, 3, 4);
    assert(fabs(q(0) - 1) < eps);
    assert(fabs(q(1) - 2) < eps);
    assert(fabs(q(2) - 3) < eps);
    assert(fabs(q(3) - 4) < eps);

    q.T().print();
    q.normalize();
    q.T().print();
    assert((q - Quatf(
                0.18257419f,  0.36514837f,  0.54772256f,  0.73029674f)
           ).norm() < eps);

    // euler to quaternion
    q = Quatf(euler_check);
    q.T().print();
    assert((q - q_check).norm() < eps);

    // euler to dcm
    Dcmf dcm(euler_check);
    dcm.print();
    assert((dcm - dcm_check).abs().max() < eps);

    // quaternion to euler
    Eulerf e1(q_check);
    assert((e1 - euler_check).norm() < eps);

    // quaternion to dcm
    Dcmf dcm1(q_check);
    assert((dcm1 - dcm_check).abs().max() < eps);

    // dcm to euler
    Eulerf e2(dcm_check);
    assert((e2 - euler_check).norm() < eps);

    // dcm to quaterion
    Quatf q2(dcm_check);
    assert((q2 - q_check).norm() < eps);

}

/* vim: set et fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */
