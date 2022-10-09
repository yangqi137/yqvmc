#ifndef YQVMC_CI_MODEL_HPP
#define YQVMC_CI_MODEL_HPP

namespace yqvmc { namespace ci {
    template <class NN_CAT>
    class IsingModel {
    public:
        typedef NN_CAT NeighborCat;
        typedef typename NeighborCat::LatticeCat LatticeCat;
        typedef typename NeighborCat::Lattice Lattice;
        typedef typename LatticeCat::Vid Vid;
        typedef Vid size_type;

        typedef typename NeighborCat::coordinationNumber
            coordinationNumber;
        typedef std::pair<size_type, double> Edge;
        typedef std::array<Edge, coordinationNumber::value> EdgeArray;

    public:
        IsingModel(const Lattice& lattice, double K)
        : m_K(K) {
            m_nv = LatticeCat::count(lattice);
            m_edges.reserve(m_nv);

            const auto cn = coordinationNumber::value;
            for (size_type v = 0; v < m_nv; v++) {
                EdgeArray edges;
                for (size_type i = 0; i < cn; i++) {
                    auto vi = NeighborCat::neighbor(v, i, lattice);
                    edges[i] = std::make_pair(vi, K);
                }

                m_edges.push_back(edges);
            }
        }

        size_type lattice_size() const { return m_nv; }

        const EdgeArray& edges_of_vertex(size_type v) const {
            //assert(v < m_edges.size());
            return m_edges[v];
        }

        template <typename Conf>
        double local_energy_diff(const Conf& conf, size_type v0) const {
            double de = 0.;
            for (auto edge : edges_of_vertex(v0)) {
                auto vi = std::get<0>(edge);
                int s = (conf[v0] == conf[vi]) ? 1 : -1;
                de += 2. * s * m_K; // Flipping parallel spins increases energy.
            }
            return de;
        }


    private:
        size_type m_nv;
        double m_K;
        std::vector<EdgeArray> m_edges;
    };
} }

#endif