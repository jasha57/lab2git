#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP
#include "tree.hpp"
#include "sequence.hpp"
#include "ArraySequence.hpp"
#include <math.h>
 
template<typename T>
struct interval{
    T start;
    T end;
    bool operator > (const interval & a){
        return a.end <= start;
    } 
    bool operator < (const interval & a){
        return a.start >= end;
    }
    bool operator == (const interval & a){
        return (a.start == start) && (a.end == end);
    }
};

template<typename T>
class dHistogram {
    private:
    Tree<int, interval<T> > res;
    inline static interval<T> tempp;
    T step;
    T min;
    int n;
    inline static int m;

    public:
    dHistogram(ArraySequence<T> & a, T _step){
        step = _step;
        n = 0;
        m = 0;
        min = a.reduce(dHistogram<T>::minF,10000000);
        T max = a.reduce(dHistogram<T>::maxF, -10000000);

        n = std::ceil(double(max-min)/step);
        for(int k = 0; k < n; k++){
            tempp = {min + k * step, min + (k + 1) * step};
            ArraySequence<bool>  ans(a.GetLenght()); 
            a.where(ans,dHistogram<T>::intervF);
            ans.map(dHistogram<T>::counter);
            res.addNode(tempp, m);
            m = 0;
        }

    }

    int info(T start, T end){
        int k = (end - start)/step;
        int s = 0;
        if((start - min)%step == 0){
            s = (start - min)/step;
        } else {
            s = (start - min)/step + 1;
        }
        int e = (end - min) / step;
        if(e > n){
            return 0;
        }
        int ret = 0;
        for(int i = 0; i < k; i++){
            ret += res.find({min + (s + i)*step,min + (s+i+1)*step});
        }
        return ret;
    }

    int info(T part){
        int s = std::ceil(double(part - min)/step);
        if(s > n){
            return 0;
        }
        return res.find({min + s* step,min + (s + 1) * step});
    }

    T minimal(){
        return min;
    }
    T maxmimal(){
        return min + n * step;
    }
    static bool intervF(T param){
            if(param >= tempp.start && param < tempp.end){
                return true;
            }
            return false;
        }

    static bool counter(bool p){
            if(p){
                m++;
            }
            return p;
        }

        static T minF(T a, T b){
            if(a > b){
                return b;
            }
            return a;
        }

        static T maxF(T a, T b){
            if(a > b){
                return a;
            }
            return b;
        }
        


};


template<class T, typename D>
class ManagerHistogram {
    private:
    ArraySequence<T> data;

    public:
    ManagerHistogram(T * _data, int size) : data(_data, size){}

    dHistogram<D> GenerateHistogram(D (*f)(T), D _step){
        ArraySequence<D> res;
        for(int i = 0; i < data.GetLenght(); i++){
            T temp = data.Get(i);
            res.Append(f(temp));
        }
        return dHistogram<D> (res, _step);
    }

};

#endif