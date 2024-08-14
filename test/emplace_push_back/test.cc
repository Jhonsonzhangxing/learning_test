// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;
 
// struct CN {
//     std::string s;
//     CN(std::string str) : s(std::move(str))  { std::cout << " constructed\n"; }
//     CN(const CN& o) : s(o.s) { std::cout << " copy constructed\n"; }
//     CN(CN&& o) : s(std::move(o.s)) { std::cout << " move constructed\n"; }
//     CN& operator=(const CN& other) {
//         s = other.s;
//         std::cout << " copy assigned\n";
//         return *this;
//     }
//     CN& operator=(CN&& other) {
//         s = std::move(other.s);
//         std::cout << " move assigned\n";
//         return *this;
//     }
// };
 
// int main()
// {
//     std::vector<CN> container;
//     // reserve enough place so vector does not have to resize
//     container.reserve(5);
//     std::cout << "construct 2 times CN:\n";
//     CN two { "two" };
//     CN three { "three" };
 
//     std::cout << "emplace:\n";
//     container.emplace(container.end(), "one");
 
//     std::cout << "emplace with CN&:\n";
//     container.emplace(container.end(), two);
    
//     std::cout << "push_back with move CN&:\n";
//     container.push_back(std::move(two));
 
//     std::cout << "emplace with CN&&:\n";
//     container.emplace(container.end(), std::move(three));
 
//     std::cout << "content:\n";
//     for (const auto& obj : container)
//         std::cout << ' ' << obj.s;
//     std::cout << '\n';
// }

// C++ program to demonstrate the
// push_back() method

#include <iostream>
#include <vector>

using namespace std;

class B {
public:
	B(int b):b_(b) { 
		cout << "B Constructor: " << b_ << endl; }
	B(const B& b):b_(b.b_) { 
		cout << "B Copy Constructor: "<< b_ << endl; }
	B(const B&& b):b_(std::move(b.b_)) { 
		cout << "B Move Constructor: " << b_ << endl; }
	B& operator=(const B& b) { 
		cout << "B = " << b_; return *this; }
	B& operator=(const B&& b) { 
		cout << "B Move = " << b_; return *this; }
	~B() { 
		cout << "B Destructor: " << b_ << endl; }
	int b_;
};


// Class
class GFG {

public:
	B x;

	// Parameterized Constructor
	GFG(B& x)
		: x(x)
	{
		cout << "Constructor=>"
			<< "x:" << x.b_ << endl;
	}

	GFG(B&& x)
		: x(std::move(x))
	{
		cout << "Move Constructor=>"
			<< "x:" << x.b_ << endl;
	}

	// Copy Constructor
	GFG(const GFG& GFG)
		: x(GFG.x)
	{
		cout << "Copied=>"
			<< "x:" << x.b_ << endl;
	}

		// Copy Constructor
	GFG(const GFG&& GFG)
		: x(std::move(GFG.x))
	{
		cout << "Move Copied=>"
			<< "x:" << x.b_ << endl;
	}
	GFG& operator=(const GFG&& GFG) {
		x = std::move(GFG.x);
		cout << "Move assigned=>"
			<< "x:" << x.b_ << endl;
		return *this;
	}
	GFG& operator=(const GFG& GFG) {
		x = GFG.x;
		cout << "assigned=>"
			<< "x:" << x.b_ << endl;
		return *this;
	}

	~GFG()
	{
		cout << "destructor=>"
			<< "x:" << x.b_ << endl;
	}
};

// Driver Code
int main()
{
	// Vector of object of GFG class
	// is created
	vector<GFG> vertices;
	cout << "length of vertices:" << vertices.size()
		<< endl;
vertices.reserve(6);
	// Inserting elements in the object
	// created using push_back() method
	// cout << endl;
	B b1(1);
	B b2(2);
	B b3(3);
	B b4(4);
	B b5(5);
	B b6(6);
		cout << endl;
	// Custom input entries
	vertices.push_back(b1);
	std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	cout << endl;

	vertices.emplace_back(b2);
	std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	cout << endl;

	vertices.push_back(std::move(b3));
		cout << endl;
	vertices.emplace_back(std::move(b4));
	cout << endl;
	// vertices.push_back(GFG(3));
	// std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	// cout << endl;

	// vertices.emplace_back(GFG(4));
	// std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	// cout << endl;

	// vertices.emplace_back(std::move(GFG(5)));
	// std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	// cout << endl;

	// vertices.push_back(std::move(GFG(6)));
	// std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	// cout << endl;

	// std::cout << "size: "<< vertices.size() << ", capacity: " << vertices.capacity() << std::endl;
	// std::vector<GFG> tmp;
	// std::cout << "size: "<< tmp.size() << ", capacity: " << tmp.capacity() << std::endl;
	// std::cout <<"move..........." <<std::endl;
	// tmp = std::move(vertices);
	// std::cout << "size: "<< tmp.size() << ", capacity: " << tmp.capacity() << std::endl;
	// std::cout <<"copy..........." <<std::endl;
	// tmp = vertices;
	// std::cout << "size: "<< tmp.size() << ", capacity: " << tmp.capacity() << std::endl;
	// std::cout <<std::endl;
	return 0;
}
