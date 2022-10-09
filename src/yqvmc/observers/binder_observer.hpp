#ifndef YQVMC_OBSERVER_BINDER_HPP
#define YQVMC_OBSERVER_BINDER_HPP

#include "../impl_/mean.hpp"
#include <vector>
#include <iostream>

namespace yqvmc {
    template <class ORDER_PARAM_OPERATOR,
    class ACC = impl_::MeanAcc<typename ORDER_PARAM_OPERATOR::result_type> >
    struct BinderObserver {
    public:
        typedef ORDER_PARAM_OPERATOR opop_type;
        typedef typename opop_type::result_type input_type;
        typedef ACC Accumulator;
        typedef typename ACC::result_type result_type;

        BinderObserver(std::string name, opop_type& op_measure,
        std::ostream& sout = std::cout)
        : m_name(name), m_opm(op_measure), m_sout(sout) {}

        template <typename Conf>
        void measure(const Conf& conf, std::size_t stamp) {
            input_type m = m_opm(conf, stamp);
            input_type m2 = m*m;
            //m_m_acc(m);
            m_m2_acc(m2);
            m_m4_acc(m2*m2);
        }

        void closeBin(std::size_t iBin) {
            //result_type m = m_m_acc.mean();
            //m_m_data.push_back(m);
            //m_m_acc.reset();
            result_type m2 = m_m2_acc.mean();
            m_m2_data.push_back(m2);
            m_m2_acc.reset();
            result_type m4 = m_m4_acc.mean();
            m_m4_data.push_back(m4);
            m_m4_acc.reset();
            result_type binder = m4/m2/m2;
            m_binder_data.push_back(binder);
            m_sout << m_name << ": " << binder << std::endl;
        }
        
        template <typename T>
        void set_data(T& root) const {
            auto& myroot = root[m_name];
            myroot["m2"] = m_m2_data;
            myroot["m4"] = m_m4_data;
            myroot["binder"] = m_binder_data;
        }

    private:
        std::string m_name;
        opop_type& m_opm;
        std::ostream& m_sout;
        Accumulator m_m2_acc;
        std::vector<result_type> m_m2_data;
        Accumulator m_m4_acc;
        std::vector<result_type> m_m4_data;
        std::vector<result_type> m_binder_data;
    };

    template <class OPOP,
    class ACC = impl_::MeanAcc<typename OPOP::result_type> >
    BinderObserver<OPOP, ACC> MakeBinderObserver(std::string name, OPOP& op_measure,
        std::ostream& sout = std::cout) {
        return BinderObserver<OPOP, ACC>(name, op_measure, sout);
    }

}

#endif