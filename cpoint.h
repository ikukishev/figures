#ifndef CPOINT_H
#define CPOINT_H

template <typename T>
class CPoint
{
public:
   CPoint():mX(0), mY(0), mZ(0) {}
   CPoint(T x, T y, T z):mX(x), mY(y), mZ(z) {}
   CPoint(const CPoint<T> &dot):mX(dot.mX), mY(dot.mY), mZ(dot.mZ) {}
   virtual ~CPoint() {}

   CPoint<T>& scale(CPoint<T> &p2, T coef);

   CPoint<T>& operator+=(const CPoint<T>& a)
   {
      mX += a.mX; mY += a.mY; mZ += a.mZ;
      return *this;
   }

   CPoint<T>& operator+=(T a)
   {
      mX += a; mY += a; mZ += a;
      return *this;
   }

   CPoint<T>& operator-=(const CPoint<T>& a)
   {
      mX -= a.mX; mY -= a.mY; mZ -= a.mZ;
      return *this;
   }

   CPoint<T>& operator-=(T a)
   {
      mX -= a; mY -= a; mZ -= a;
      return *this;
   }

   CPoint<T>& operator*=(const CPoint<T>& a)
   {
      mX *= a.mX; mY *= a.mY; mZ *= a.mZ;
      return *this;
   }

   CPoint<T>& operator*=(T a)
   {
      mX *= a; mY *= a; mZ *= a;
      return *this;
   }

   T mX;
   T mY;
   T mZ;
};

template <typename T>
CPoint<T> operator+(const CPoint<T>& a, const CPoint<T>& b)
{
   return CPoint<T>(a.mX + b.mX, a.mY + b.mY, a.mZ + b.mZ);
}

template <typename T>
CPoint<T> operator+(const CPoint<T>& a, T b)
{
   return CPoint<T>(a.mX + b, a.mY + b, a.mZ + b);
}

template <typename T>
CPoint<T> operator+(T a, const CPoint<T>& b)
{
   return CPoint<T>(a + b.mX, a + b.mY, a + b.mZ);
}

template <typename T>
CPoint<T> operator-(const CPoint<T>& a, const CPoint<T>& b)
{
   return CPoint<T>(a.mX - b.mX, a.mY - b.mY, a.mZ - b.mZ);
}

template <typename T>
CPoint<T> operator-(const CPoint<T>& a, T b)
{
   return CPoint<T>(a.mX - b, a.mY - b, a.mZ - b);
}

template <typename T>
CPoint<T> operator-(T a, const CPoint<T>& b)
{
   return CPoint<T>(a - b.mX, a - b.mY, a - b.mZ);
}

template <typename T>
CPoint<T> operator*(const CPoint<T>& a, const CPoint<T>& b)
{
   return CPoint<T>(a.mX * b.mX, a.mY * b.mY, a.mZ * b.mZ);
}

template <typename T>
CPoint<T> operator*(const CPoint<T>& a, T b)
{
   return CPoint<T>(a.mX * b, a.mY * b, a.mZ * b);
}

template <typename T>
CPoint<T> operator*(T a, const CPoint<T>& b)
{
   return CPoint<T>(a * b.mX, a * b.mY, a * b.mZ);
}

template <typename T>
CPoint<T>& CPoint<T>::scale(CPoint<T> &p2, T coef)
{
   this->operator -=(p2);
   this->operator *=(coef);
   this->operator +=(p2);
   return *this;
}

#endif // CPOINT_H
