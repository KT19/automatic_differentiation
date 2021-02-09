#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

class Tensor {
protected:
  double value;
  double gradient;
  vector<pair<Tensor*, double>> parents; //parents_node, local_gradient

public:
  Tensor(){}
  Tensor(double x) : value(x), gradient(0.0) {} //constructor
  void backward(void);
  double backward(double out);
  double data(void) {return this->value; }
  double grad(void) {return this->gradient; }

  //tensor with tensor
  friend Tensor& operator * (Tensor &left, Tensor &right);
  friend Tensor& operator + (Tensor &left, Tensor &right);
  friend Tensor& operator - (Tensor &left, Tensor &right);

  //double with tensor
  friend Tensor& operator * (double other, Tensor &right);

  //mathmatics
  friend Tensor& exp(Tensor &x);
};

class MulTensor : public Tensor {
public:
  MulTensor(Tensor* left, Tensor* right) {
    this->value = left->data()*right->data();
    this->parents.push_back({left, right->data()});
    this->parents.push_back({right, left->data()});
  }
  MulTensor(double other, Tensor* right) {
    this->value = other*right->data();
    this->parents.push_back({right, other});
  }
};

class AddTensor : public Tensor {
public:
  AddTensor(Tensor* left, Tensor* right) {
    this->value = left->data()+right->data();
    this->parents.push_back({left, 1.0});
    this->parents.push_back({right, 1.0});
  }
};

class SubTensor : public Tensor {
public:
  SubTensor(Tensor* left, Tensor* right) {
    this->value = left->data()-right->data();
    this->parents.push_back({left, 1.0});
    this->parents.push_back({right, -1.0});
  }
};

//mathematics
class ExpTensor : public Tensor {
public:
  ExpTensor(Tensor *x) {
    this->value = exp(x->data());
    this->parents.push_back({x, this->value});
  }
};

//function
void Tensor::backward(void) {
  this->gradient = 1.0;
  for(auto par: this->parents) {
    par.first->backward(1.0*par.second);
  }

  return;
}

double Tensor::backward(double out) {
  double sum = out;

  for(auto par: this->parents) {
    double local_gradient = out*par.second;
    par.first->backward(local_gradient);
    sum += local_gradient;
  }

  return this->gradient += sum;
}

//operator
//tensor with tensor
Tensor& operator * (Tensor &left, Tensor &right) {
  return *new MulTensor(&left, &right);
}

Tensor& operator + (Tensor &left, Tensor &right) {
  return *new AddTensor(&left, &right);
}

Tensor& operator - (Tensor &left, Tensor &right) {
  return *new SubTensor(&left, &right);
}
//double with tensor
Tensor& operator * (double other, Tensor &right) {
  return *new MulTensor(other, &right);
}

//mathematics
Tensor& exp(Tensor &x) {
  return *new ExpTensor(&x);
}

int main(void) {
  Tensor x(2.0);
  Tensor y(-3.0);

  //(x^2)y - 2y + x where x=2.0, y=-3.0
  Tensor f = x*x*y - 2*y + x;

  cout<<"function value = ";
  cout<<f.data()<<endl;
  f.backward(); //reverse mode automatic differentiation
  cout<<"gradient ∂f/∂x = "<<x.grad()<<" gradient ∂f/∂y = "<<y.grad()<<endl;

  return 0;
}
