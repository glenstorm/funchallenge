#include <iostream>
#include <boost/coroutine2/all.hpp>
#include <sstream>
#include <stdexcept>

class Parser{
   char next;
   std::istream& is;
   std::function<void(char)> cb;

   char pull(){
        return std::char_traits<char>::to_char_type(is.get());
   }

   void scan(){
       do{
           next=pull();
       }
       while(isspace(next));
   }

public:
   Parser(std::istream& is_,std::function<void(char)> cb_) :
      next(), is(is_), cb(cb_)
    {}

   void run() {
      std::cout << "run" << std::endl;
      scan();
      E();
   }

private:
   void E(){
	   std::cout << "E" << std::endl;
      T();
      while (next=='+'||next=='-'){
         cb(next);
         scan();
         T();
      }
   }

   void T(){
	   std::cout << "T" << std::endl;
      S();
      while (next=='*'||next=='/'){
         cb(next);
         scan();
         S();
      }
   }

   void S(){
	   std::cout << "S" << std::endl;
      if (std::isdigit(next)){
         cb(next);
         scan();
      }
      else if(next=='('){
         cb(next);
         scan();
         E();
         if (next==')'){
             cb(next);
             scan();
         }else{ 
             throw std::logic_error( "parse error" );
         }
      }
      else{
         throw std::logic_error( "parse error");
      }
   }
};

typedef boost::coroutines2::coroutine< char > coro_t;

int main() {
    std::istringstream is("(1+1)*2/4");
    // invert control flow
    coro_t::pull_type seq(
            boost::coroutines2::fixedsize_stack(),
            [&is](coro_t::push_type & yield) {
                // create parser with callback function
                Parser p( is,
                          [&yield](char ch){
                            // resume user-code
                            yield(ch);
                          });
                // start recursive parsing
                p.run();
            });

    // user-code pulls parsed data from parser
    // invert control flow
    for(char c:seq){
        printf("Parsed: %c\n",c);
    }
}
