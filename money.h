/* 
 * File:   money.h
 * Author: arun
 *
 * Created on September 16, 2013, 12:50 AM
 */

#ifndef MONEY_H
#define	MONEY_H

#ifdef	__cplusplus
extern "C" {
#endif

class Money
  {
    public:

        Money();                        // Initialize to 0.00
        Money(int dollars);             // Exact dollar amount - no cents
        Money(int dollars, long cents);

        Money operator +    (const Money & other) const;
        Money operator -    (const Money & other) const;
        Money & operator += (const Money & other);
        Money & operator -= (const Money & other);

        int dollars() const;
        int cents() const;

        // All other comparisons can be done in terms of these two
        // (actually just < is strictly needed!)
     
        bool operator == (const Money & other) const;
        bool operator <  (const Money & other) const;

    private:

        unsigned long _cents;
  };


#ifdef	__cplusplus
}
#endif

#endif	/* MONEY_H */

