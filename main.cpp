/**
 *
 * @file     FunctorSort.cpp
 *
 * @authors  M. Laporte, D. Mathieu
 *
 * @date     07/12/2011
 *
 * @version  V1.0
 *
 **/
#include <string>
#include <vector>
#include <algorithm> // sort()
#include <iostream>

using namespace std;

namespace
{
    template <typename TRes, typename T>
    class IPredicateGen
    {
      public :
        virtual ~IPredicateGen (void) {}
        virtual TRes operator () (const T &) const = 0;

    }; // ILessThanGen

    class Pers
    {
        string   myNom;
        unsigned myAge;

      public :
        Pers (const string & Nom, unsigned Age)
            : myNom (Nom), myAge (Age) {}

        const string & getNom (void) const noexcept { return myNom; }
        unsigned       getAge (void) const noexcept { return myAge; }

    private :
        ostream & display (ostream & os)  const
        {
            return os << getAge () << " - " << getNom ();

        } // display()

      public :
        friend ostream & operator << (ostream & os, const Pers & p)
        {
            return p.display (os);

        }

    }; // Pers

    class SelParTrancheAge : public IPredicateGen <bool, Pers>
    {
    private:
        unsigned myAgeMin;
        unsigned myAgeMax;

      public :
        SelParTrancheAge(unsigned ageMin, unsigned ageMax) : myAgeMin(ageMin), myAgeMax(ageMax) {}
        virtual ~SelParTrancheAge (void) noexcept {}

        virtual bool operator () (const Pers & p)
                        const noexcept
        {
            return p.getAge () <= myAgeMax && p.getAge() >= myAgeMin;

        } // operator ()

    }; // TriParAgeAsc

    class SelParNomMin : public IPredicateGen <bool, Pers>
    {
    private:
        string myNomMin;

      public :
        SelParNomMin(const string& nomMin) : myNomMin(nomMin) {}
        virtual ~SelParNomMin (void) noexcept {}

        virtual bool operator () (const Pers & p)
                        const noexcept
        {
            return p.getNom() >= myNomMin;

        } // operator ()

    }; // TriParAgeAsc

    void functorFind (void)
        {
            cout << "FunctorFind : \n";

            typedef vector <Pers> CVPers;
            CVPers vPers;

            vPers.push_back ( Pers ("Charlotte", 21));
            vPers.push_back ( Pers ("Alfred",    12));
            vPers.push_back ( Pers ("Jean",      42));
            vPers.push_back ( Pers ("Noemie",    11));
            vPers.push_back ( Pers ("Berthe",    99));
            vPers.push_back ( Pers ("Agathe",    29));
            vPers.push_back ( Pers ("Sylvain",   42));
            vPers.push_back ( Pers ("Pierre",    75));

            for (const Pers & personne : vPers)
                cout << personne << '\n';

            CVPers::const_iterator pos;

            cout << "\nRecherche sur  43 <= age <= 75 : ";

            pos = find_if (vPers.begin (), vPers.end (), SelParTrancheAge(43, 75)); // a completer
            if (vPers.end () == pos)
                cout << "Aucun element ne correspond a ce critere\n";
            else
                cout << *pos << '\n';

            cout << "\nRecherche sur  43 <= age <= 45 : ";

            pos = find_if (vPers.begin (), vPers.end (), SelParTrancheAge(43, 45));// a completer
            if (vPers.end () == pos)
                cout << "Aucun element ne correspond a ce critere\n";
            else
                cout << *pos << '\n';

            cout << "\nRecherche nom >= Toto : ";

            pos = find_if (vPers.begin (), vPers.end (), SelParNomMin("aaa"));// a completer
            if (vPers.end () == pos)
                cout << "Aucun element ne correspond a ce critere\n";
            else
                cout << *pos << '\n';




            cout << '\n';

        } // functorFind()

} // namespace

int main (void)
{
    functorFind ();

    return 0;

} // main()
