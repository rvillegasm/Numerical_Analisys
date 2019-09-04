#include <stddef.h>
#include "incrementalSearch.h"

/*
    Implementation:
    ---------------
    First, the initial value is evaluated in the function. 
    If said value is 0, then the initial value is a root, 
    so the algorithm returns an interval from the initial value to itself
    and finishes.

    Otherwise, a second value is defined by adding a delta to the inital value,
    creating an interval between the initial value and itself. 
    The second value is then evaluated in the function.

    Then we check if the two values evaluated in the function are of the same sign.
    If they are, and we have not exceeded the max number of iterations, we move the
    interval by delta units.

    When we get out of the loop, we check if the second value of the interval is 0.
    If it is, then it is a root, so an interval second value to itslef is returned and 
    the algorithm finishes.
    Else if the two values evaluated on the function are of different sign, 
    we have found an interval containing a root, so we return said interval
    and finish.

    If none of the above conditions are true, then we have found nothing,
    so the algorithm returns an interval from 0 to 0, 
    and we specify that it wasn't successful.
 */
int incrementalSearch(double (*func)(double), double x0, double delta, int nIter, double *retVal0, double *retVal1) {
    
    double fx0, x1, fx1;
    // Interval interval = {0, 0, false, false};
    
    fx0 = func(x0);
    if (fx0 == 0) {
        // x0 is a root
        *retVal0 = x0;
        retVal1 = NULL;
        // interval.first = x0;
        // interval.last = x0;
        // interval.wasSuccessful = true;
        // interval.isRoot = true;

        return nIter;
    }
    else {
        x1 = x0 + delta;
        fx1 = func(x1);
        while (fx0 * fx1 > 0 && --nIter > 0) {
            x0 = x1;
            fx0 = fx1;
            x1 = x0 + delta;
            fx1 = func(x1);
        }

        if (fx1 == 0) {
            // x1 is a root
            *retVal1 = x1;
            retVal0 = NULL;
            // interval.first = x1;
            // interval.last = x1;
            // interval.wasSuccessful = true; 
            // interval.isRoot = true;

            return nIter;
        }
        else if (fx0 * fx1 < 0) {
            // [x0, x1] contains a root
            *retVal0 = x0;
            *retVal1 = x1;
            // interval.first = x0;
            // interval.last = x1;
            // interval.wasSuccessful = true;

            return nIter;
        }
        // The algorithm wasn't successful
        return NULL;
    }    
}