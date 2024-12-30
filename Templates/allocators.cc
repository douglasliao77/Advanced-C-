#include <cassert>
#include <iostream>
#include <string>
#include <utility>

template <typename T>
struct New_allocator {

    template <typename... Args>
    static T* create(Args&&... args) {
        return new T {std::forward<Args>(args)...};
    }

    static void destroy(T* data) {
        delete data;
    }
};

template <typename T>
struct Tracker_Allocator {
    
    template <typename... Args>
    static T* create(Args&&... args) {
        T* result { New_allocator<T>::create(std::forward<Args>(args)...) };
        std::cout << "Object allocated at " << result << std::endl;
        return result;
    }

    static void destroy(T* data) {
        std::cout << "Object deallocating at " << data << std::endl;
        New_allocator<T>::destroy(data);
    }
};


template <typename T, template <typename> typename Allocator = New_allocator>
class Stack
{

  struct Node;
  
public:

  Stack()
    : head{nullptr} { }

  Stack(Stack const&) = delete;
  Stack(Stack&&) = delete;

  Stack& operator=(Stack const&) = delete;
  Stack& operator=(Stack&&) = delete;
  
  ~Stack()
  {
    while (!empty())
    {
      pop();
    }
  }
  
  void push(T const& value)
  {
    head = Allocator<Node>::create(value, head);
  }

  T pop()
  {
    T result{top()};
    Node* old {head};
    head = head->next;
    Allocator<Node>::destroy(old);
    return result;
  }

  T& top()
  {
    return head->value;
  }

  T const& top() const
  {
    return head->value;
  }

  bool empty() const
  {
    return head == nullptr;
  }
  
private:
  
  struct Node
  {
    T value;
    Node* next;
  };

  Node* head;
  
};

int main()
{
  {
    Stack<std::string> st {};
    assert(st.empty());
  
    st.push("1");
    assert(!st.empty());
    assert(st.top() == "1");
  
    st.push("2");
    assert(st.top() == "2");
    assert(st.pop() == "2");
  
    assert(st.pop() == "1");

    assert(st.empty());

    st.push("3");
    assert(st.pop() == "3");
    
    st.push("4");
    
    st.push("5");
    assert(st.pop() == "5");
  }
  {
    Stack<std::string, Tracker_Allocator> st {};
    assert(st.empty());
  
    st.push("1");
    assert(!st.empty());
    assert(st.top() == "1");
  
    st.push("2");
    assert(st.top() == "2");
    assert(st.pop() == "2");
  
    assert(st.pop() == "1");

    assert(st.empty());
    
    st.push("3");
    assert(st.pop() == "3");
    
    st.push("4");
    
    st.push("5");
    assert(st.pop() == "5");
  }
}