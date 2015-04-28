#ifndef _SHIPWRECK_HH_
#define _SHIPWRECK_HH_

#include <typeinfo>
#include <algorithm>
#include <iostream>
#include <tuple>


/* Wyposażenie statku */
template <unsigned int CAN, unsigned int MAS, unsigned int OAR>
struct ShipGear
{
    static constexpr unsigned int cannons = CAN;
    static constexpr unsigned int masts = MAS;
    static constexpr unsigned int oars = OAR;
};

/* Pojedyncze elementy statku (reprezentanci) */
typedef ShipGear<1, 0, 0> Cannon;
typedef ShipGear<0, 1, 0> Mast;
typedef ShipGear<0, 0, 1> Oar;

/* Suma wyposażenia zawartego w G1 i G2 */
template <class G1, class G2>
struct add_gear
{
    typedef ShipGear<
                      G1::cannons + G2::cannons,
                      G1::masts + G2::masts,
                      G1::oars + G2::oars
                     > type;
};

/* Wyposażenie G1 pomniejszone o wyposażenie G2 (bez ujemnych liczb) */
template <class G1, class G2>
struct remove_gear
{
    static const unsigned int subtr_cannons =
                      G1::cannons > G2::cannons ? G1::cannons - G2::cannons : 0;
    static const unsigned int subtr_masts =
                              G1::masts > G2::masts ? G1::masts - G2::masts : 0;
    static const unsigned int subtr_oars =
                                  G1::oars > G2::oars ? G1::oars - G2::oars : 0;
    typedef ShipGear<subtr_cannons, subtr_masts, subtr_oars> type;
};

/* Wyposażenie zawarte w G1 powiększone N razy */
template <class G1, unsigned int N>
struct multiply_gear
{
    typedef ShipGear<G1::cannons * N, G1::masts * N, G1::oars * N> type;
};

/* Wyposażenie zawarte w G1 podzielone na N równych części (reszta z dzielenia
 * przepada) */
template <class G1, unsigned int N>
struct split_gear
{
    static_assert(N > 0, "Avoiding division by zero (N = 0).");
    typedef ShipGear<(G1::cannons / N), (G1::masts / N), (G1::oars / N)> type;
};


/* Reprezentuje bandę okrętów, parametryzowaną wyposażeniem pojedynczego okrętu
 * w oddziale */
template <class Gear>
class Squad
{
    private:
        unsigned int count;

    public:
        typedef Gear gear_type;

        static gear_type gear;

        Squad() : count(1) {};
        Squad(unsigned int const n) : count(n) {};
        Squad(Squad<Gear> const & sq) : count(sq.get_count()) {};

        /* Zwraca liczność bandy */
        unsigned int get_count() const
        {
            return count;
        }

        /* Decyduje liczba dział na pojedynczym statku */
        template <class G>
        bool operator<(const Squad<G> & sq) const
        {
            return (Gear::cannons < G::cannons);
        }

        template <class G>
        bool operator>(const Squad<G> & sq) const
        {
            return (Gear::cannons > G::cannons);
        }

        template <class G>
        const bool operator>=(const Squad<G> & sq)
        {
            return (Gear::cannons >= G::cannons);
        }

        template <class G>
        bool operator<=(const Squad<G> & sq) const
        {
            return (Gear::cannons <= G::cannons);
        }

        template <class G>
        bool operator==(const Squad<G> & sq) const
        {
            return (Gear::cannons == G::cannons);
        }

        template <class G>
        bool operator!=(const Squad<G> & sq) const
        {
            return (Gear::cannons != G::cannons);
        }

        const Squad<Gear> operator+(const Squad<Gear> & sq)
        {
            return Squad<Gear>(count + sq.get_count());
        }

        const Squad<Gear> & operator+=(const Squad<Gear> & sq)
        {
            count += sq.get_count();
            return * this;
        }

        const Squad<Gear> operator-(const Squad<Gear> & sq)
        {
            return Squad<Gear>((count > sq.get_count() ? count -
                                                          sq.get_count() : 0));
        }

        const Squad<Gear> & operator-=(const Squad<Gear> & sq)
        {
            count = (count > sq.get_count() ? count -
                                                           sq.get_count() : 0);
            return * this;
        }

        const Squad<Gear> operator*(const unsigned int n)
        {
            return Squad<Gear>(count * n);
        }

        const Squad<Gear> & operator*=(const unsigned int n)
        {
            count *= n;
            return * this;
        }

        const Squad<Gear> operator/(const unsigned int n)
        {
            return Squad<Gear>(count / n);
        }

        const Squad<Gear> & operator/=(const unsigned int n)
        {
            count /= n;
            return * this;
        }

        bool operator==(const Squad<Gear> & sq) const
        {
            return (count == sq.get_count());
        }

        bool operator!=(const Squad<Gear> & sq) const
        {
            return (count != sq.get_count());
        }

        bool operator<(const Squad<Gear> & sq) const
        {
            return (count < sq.get_count());
        }

        bool operator>(const Squad<Gear> & sq) const
        {
            return (count > sq.get_count());
        }

        bool operator<=(const Squad<Gear> & sq) const
        {
            return (count <= sq.get_count());
        }

        bool operator>=(const Squad<Gear> & sq) const
        {
            return (count >= sq.get_count());
        }
};

/* Wypisywanie bandy */
template <class G>
std::ostream & operator<<(std::ostream & os, const Squad<G> & sq)
{
        return os << "Ships: " << sq.get_count() << "; Ship gear: Cannons: " <<
            G::cannons << ", Masts: " << G::masts << ", Oars: " << G::oars;
}

template <class G>
const Squad<G> operator*(const unsigned int n, const Squad<G> & squad)
{
    Squad<G> resu = squad;
    return resu * n;
}

/* Tworzy bandę nowych, mocniejszych okrętów. Każda cecha stanowi sumę
 * odpowiednich cech dwóch starych band, a liczność bandy określamy przez
 * dostępną ilość sprzętu.  */
template <class Gear, class OtherGear>
Squad<typename add_gear<Gear, OtherGear>::type> const 
join_ships(Squad<Gear> const & sq1, Squad<OtherGear> const & sq2)
{
    typedef typename add_gear<Gear, OtherGear>::type JointGear;
    int by_cannons, by_masts, by_oars;

    if (JointGear::cannons > 0)
        by_cannons = (Gear::cannons * sq1.get_count() +
                              OtherGear::cannons * sq2.get_count()) /
                              JointGear::cannons;
    else
        by_cannons = -1;

    if (JointGear::masts > 0)
        by_masts = (Gear::masts * sq1.get_count() +
                         OtherGear::masts * sq2.get_count()) / JointGear::masts;
    else
        by_masts = by_cannons;

    if (JointGear::oars > 0)
        by_oars = (Gear::oars * sq1.get_count() +
                           OtherGear::oars * sq2.get_count()) / JointGear::oars;
    else
        by_oars = by_masts;

    if (by_cannons == -1)
    {
        if (by_masts == -1)
        {
            if (by_oars == -1)
                return Squad<JointGear>(sq1.get_count() +
                                                        sq2.get_count());
            else
                return Squad<JointGear>(by_oars);
        }
        else
            return Squad<JointGear>(std::min(by_oars, by_masts));
    }

    return Squad<JointGear>(std::min({by_cannons, by_masts, by_oars}));
}

/* Dzieli bandę na dwie nowe o tej samej liczności, złożone z mniejszych 
 * okrętów.  Każda cecha stanowi iloraz starej wartości cechy przez 2, reszta 
 * z dzielenia przepada. */
template <class Gear>
Squad<typename split_gear<Gear, 2>::type> const split_ships(Squad<Gear> const & sq)
{
    return Squad<typename split_gear<Gear, 2>::type>(sq.get_count());
}

/* Tworzy krotkę std::tuple na podstawie ShipGear */
template<class Gear>
constexpr std::tuple<unsigned, unsigned, unsigned> to_tuple()
{ 
    return std::tuple<
                      unsigned,
                      unsigned,
                      unsigned
                     > (Gear::cannons, Gear::masts, Gear::oars);
};

/* Przyjmuje wartość true, gdy łupem staje się banda o wyposażeniu Gear, false
 * - gdy OtherGear */
template <class Gear, class OtherGear>
struct is_bigger
{
    constexpr is_bigger();
    constexpr static bool check()
    {
        return to_tuple<Gear>() < to_tuple<OtherGear>();
    }
    static const bool value = check();
};

/* Dla Cond = true ustawia pierwszy z obiekt jako wynik */
template<class X, class Y, bool Cond >
struct expected_booty_helper
{ 
    typedef X result_type;
    const X& result;
    expected_booty_helper(const X &x, const Y &y) : result(x) {}
};

/* Dla Cond = false ustawia drugi z obiekt jako wynik */
template<class X, class Y>
struct expected_booty_helper<X, Y, false>
{
    typedef Y result_type;
    const Y& result;
    expected_booty_helper(const X &x, const Y &y) : result(y) {}
};

/* Przekazuje w wyniku obiekt reprezentujący bandę, która
   będzie oczekiwanym łupem w konflikcie dwóch band. */
template <class Gear, class OtherGear>
typename expected_booty_helper<
                               Squad<Gear>,
                               Squad<OtherGear>,
                               is_bigger<Gear, OtherGear>::value
                              >::result_type
expected_booty(const Squad<Gear> &a, const Squad<OtherGear> &b)
{
    expected_booty_helper<
                          Squad<Gear>,
                          Squad<OtherGear>,
                          is_bigger<Gear,OtherGear>::value
                         > resu(a,b);
    return resu.result;
}


#endif
