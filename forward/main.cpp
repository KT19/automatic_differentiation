#include<iostream>
#include<cmath>

using namespace std;

class Tensor {
private:
  double data;
  double grad;

public:
  Tensor(void) : data(0.0), grad(0.0) {}
  Tensor(double data) : data(data), grad(0.0) {}
  Tensor(double data, double seed) : data(data), grad(seed) {}
  double getVal(void) {
    return this->data;
  }
  double getGradient(void) {
    return this->grad;
  }
  //operator
  friend Tensor operator * (const Tensor &left, const Tensor &right);
  friend Tensor operator * (double val, const Tensor &right);
  friend Tensor operator + (const Tensor &left, const Tensor &right);
  friend Tensor operator - (const Tensor &left, const Tensor &right);
  //math
  friend Tensor power(const Tensor &x, double p);
};

//operator
Tensor operator * (const Tensor &left, const Tensor &right) {
  return Tensor(left.data*right.data, left.data*right.grad + left.grad*right.data);
}
Tensor operator * (double val, const Tensor &right) {
  return Tensor(val*right.data, right.grad);
}
Tensor operator + (const Tensor &left, const Tensor & right) {
  return Tensor(left.data+right.data, left.grad + right.grad);
}
Tensor operator - (const Tensor &left, const Tensor &right) {
  return Tensor(left.data-right.data, left.grad - right.grad);
}

//math
Tensor power(const Tensor &x, double p) {
  return Tensor(pow(x.data, p), p*x.grad*pow(x.data, p-1));
}


int main(void) {
  Tensor x(1.0, 1.0); //the gradient w.r.t. x
  Tensor y(1.0);

  //calculate gradient of (x^2)y-2y+x w.r.t. x where x=1, y=1
  Tensor f = power(x,2)*y - 2*y + x;

  cout<<"value = "<<f.getVal()<<", grad = "<<f.getGradient()<<endl;

  return 0;
}
