#include <vector>

template < typename T, typename E>
class Result {
  public:

    Result<T, E>(){
      _value = NULL;
    }

    Result<T, E>(const T& value){
      this->_value = new T(value);
    }

    Result<T, E>(const T& value, E* error){
      this->_value = new T(value);
      _errors.push_back(error);
    }

    Result<T, E>(E* error){
      _value = NULL;
      _errors.push_back(error);
    }

    Result<T, E>(std::vector<E*>& errors){
      this->_value = 0;
      int size = _errors.size();

      for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(errors[i])));
      }
    }

    Result<T, E>(const Result<T, E>& other){
      if (other._value) {
        this->_value = new T(*other._value);
      } else {
        this->_value = NULL;
      }

      int size = other._errors.size();

      for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(other._errors[i])));
      }
    }

    ~Result<T, E>(){
      delete _value;
      int errorsSize = _errors.size();
      for (int i = 0; i < errorsSize; i++) {
        delete _errors[i];
      }
    }

    static Result<T, E> ok(const T& value) {
      return Result<T, E>(value);
    }

    static Result<T, E> warning(const T& value, E* error) {
      return Result<T, E>(value, error);
    }

    static Result<T, E> fail(E* error) {
      return Result<T,E>(error);
    }

    static Result<T, E> fail(std::vector<E*>& errors) {
      return Result<T, E>(errors);
    }

    Result<T, E>& operator=(const Result<T, E>& other) {
      if (this != &other) {
        delete this->_value;

        if (other._value)
          this->_value = new T(*other._value);
        else
          this->_value = NULL;

        this->_errors = other._errors;
      }
      return *this;
    }

    bool isSuccess(){
      return this->_value != NULL;
    }

    bool errorsExist() {
      return _errors.empty();
    }

    T& getValue(){
      return *this->_value;
    }

    std::vector<E*>& getErrors(){
      return this->_errors;
    }

    void joinErrors(const Result<T, E>& other) {
      int size = other._errors.size();
      for (int i = 0; i < size; i++) {
        E* copied_error = new E(*(other._errors[i]));
        this->_errors.push_back(copied_error);
      }
    }

    void addValue(const T& val) {
      _value =  new T(val);
    }

    void addError(E* error) {
      _errors.push_back(error);
    }

    std::string errorsToString() {
      std::string result = "";
      int size = _errors.size();
      for (int i = 0; i < size; i++) {
        if (!result.empty()) {
          result += "\n";
        }
        result += _errors[i]->toString();
      }
      return result;
    }

  private:
    T *_value;
    std::vector<E*> _errors;
};

template<typename E>
class Result<void, E> {
public:
    Result() {}

    Result<void, E>(E* error){
      _errors.push_back(error);
    }

    Result<void, E>(std::vector<E*>& errors){
      this->_errors = errors;
    }

    Result<void, E>(const Result<void, E>& other){
      int size = other._errors.size();

      for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(other._errors[i])));
      }
    }

    static Result<void, E> ok(){
      Result<void, E> res;
      res._success = true;
      return res;
    }

    static Result<void, E> warning(E* error) {
      Result<void, E> res(error);
      res._success = true;
      return res;
    }

    static Result<void, E> fail(E* error) {
      Result<void, E> res(error);
      res._success = false;
      return res;
    }

    static Result<void, E> fail(std::vector<E*>& errors) {
      Result<void, E> res(errors);
      res._success = false;
      return res;
    }

    std::string errorsToString() {
      std::string result = "";
      int size = _errors.size();
      for (int i = 0; i < size; i++) {
        if (!result.empty()) {
          result += "\n";
        }
        result += _errors[i]->toString();
      }
      return result;
    }

    void addError(E* error) {
        _errors.push_back(error);
    }

    bool isSuccess() const {
        return _success;
    }

    bool errorsExist() {
      return !_errors.is_empty();
    }

    void joinErrors(const Result<void, E>& other) {
      int size = other._errors.size();
      for (int i = 0; i < size; i++) {
        E* copied_error = new E(*(other._errors[i]));
        this->_errors.push_back(copied_error);
      }
    }
    
private:
    std::vector<E*> _errors;
    bool _success;
};
