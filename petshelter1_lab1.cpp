

//Program Written by and Tahir

// Practice program to review
//loops, functions, dynamic allocation,
//pointers, structures, arrays,
//input and output, conditionals,
//and other programming basics

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Cat
{
public:
    // Constructor for name, hair, color and ID
    Cat(std::string n, std::string h, std::string c, std::string i);
        
    // Member functions to set the name, hair and color of the cat
    void set_name(std::string new_name);
    void set_hair(std::string new_hair);
    void set_color(std::string new_color);
        
    // Member functions to get the name, hair and color of the cat
    std::string get_name() const;
    std::string get_hair() const;
    std::string get_color() const;
        
    // Member functions to get the days in shelter and ID of the cat
    int get_days_in_shelter() const;
    std::string get_id() const;
        
    // Misc
    void increment_days_in_shelter();
    
    
    
private:
    // Private member variables to store the name, hair, color, ID and days in shelter of the cat
    std::string name;
    std::string hair;
    std::string color;
    std::string id;
    int days_in_shelter;
    static int next_id;
};

// Definition of the member function to set the name of the cat
void Cat::set_name(std::string new_name)
{
    name = new_name;
}

// Definition of the member function to set the hair of the cat
void Cat::set_hair(std::string new_hair)
{
    hair = new_hair;
}

// Definition of the member function to set the color of the cat
void Cat::set_color(std::string new_color)
{
    color = new_color;
}

// Definition of the amember function to get the name of the cat
std::string Cat::get_name() const
{
    return name;
}

// Definition of the member function to get the hair of the cat
std::string Cat::get_hair() const
{
    return hair;
}

// Definition of the member function to get the color of the cat
std::string Cat::get_color() const
{
    return color;
}

// Definition of the member function to get the days in shelter of the cat
int Cat::get_days_in_shelter() const 
{
    return days_in_shelter;
}

// Definition of the member function to get the ID of the cat
std::string Cat::get_id() const
{
    return id;
}

// Definition of the member function to increment the days in shelter of the cat
void Cat::increment_days_in_shelter()
{
    days_in_shelter++;
}

// Definition of the constructor for Cat class
Cat::Cat(std::string n, std::string h, std::string c, std::string i)
{
    name = n;
    hair = h;
    color = c;
    id = i;
    days_in_shelter = -1;
}

// Definition of the static member variable next_id to start id integer at 1
int Cat::next_id = 1;

// Function to generate a unique ID for each cat
std::string generate_id(int index)
{
    return "A"  + std::to_string(index + 1);
}



// Constant integer to store the number of cats
const int NUM_CATS = 5;


int main()
{
    //Declaring variables to store pet's name, hair type and color
    std::string new_hair;
    std::string new_color;
    std::string new_name;
    //keeps track of how many times the user has inputted a pet and its info
    int count = 0;
    //keeps track of remaining spots in file for input(Path A)
    int file_count = 0;
    std::string input;
    //Declaring an array of objects of the class 'Cat' with a size of NUM_CATS
    Cat shelter[NUM_CATS] = {
    Cat(" ", " ", " ", " "),
    Cat(" ", " ", " ", " "),
    Cat(" ", " ", " ", " "),
    Cat(" ", " ", " ", " "),   
    Cat(" ", " ", " ", " "),
    };
    

    /****************************
    Path A for User To enter in their own text file
    *****************************/
    std::cout << "Do you have current inventory? (Y/N) ";
    std::cin >> input;

    if (input == "Y" || input == "y")
    {
        std::string filename;
        std::ifstream input_file;
        do
        {
            std::cout << "Please enter the name of the file to read in: ";
            std::cin >> filename;
            input_file.open(filename);
            if (!input_file)
            {
                std::cerr << "Error opening file, Please try again." << std::endl;
            }
        } 
        while (!input_file);


        // Initialize variables
        int last_num = 0; // This variable will store the last number in a cat ID
        std::string last_line; // This variable will store each line read from the input file
        
        // Read the input file line by line
        while (std::getline(input_file, last_line))
        {
            // Parse the current line into individual fields
            std::stringstream ss(last_line);
            std::string new_id, new_name, new_hair, new_color;
            int days_in_shelter;
            ss >> new_id >> new_name >> new_hair >> new_color >> days_in_shelter;
            
            
            // Check if the ID of the current cat is greater than the last number
            if (new_id.length() > 3 && isdigit(new_id[new_id.length() - 1]))
            {
                last_num = std::max(last_num, stoi(new_id.substr(3)));
            }
            
            // If there is still space in the array of cats, create a new cat object and add it to the array
            if (count < NUM_CATS)
            {
                shelter[count] = Cat(new_name, new_hair, new_color, new_id);
                count++;
            }
            // Otherwise, break out of the loop and output an error message
            else
            {
                std::cout << "The file contains the maximum number of cats. You cannot add more cats." << std::endl;
                break;
            }
        
        }
        
        input_file.close();
        
        if (count < NUM_CATS)
        {
            std::cout << "There are " << NUM_CATS - count << " spots left for input." << std::endl;
        }
        else
        {
            std::cout << "The shelter is full. You cannot add more cats." << std::endl;
        }
    
        while (count < NUM_CATS)
        {
            std::string new_name, new_hair, new_color;
            std::cout << "Please enter the pet's name, hair type, and color or -1 to exit: " << std::endl;
            std::cout << "Name: ";
            std::cin >> new_name;
            if (new_name == "-1")
            {
                break;
            }
            std::cout << "Hair type: ";
            std::cin >> new_hair;
            std::cout << "Color: ";
            std::cin >> new_color;
            
            std::string new_id = "CAT" + std::to_string(last_num + 1);
            shelter[count] = Cat(new_name, new_hair, new_color, new_id);
            count++;
            last_num++;
        }
    
        std::cout << "Please enter the name of the file to write out: ";
        std::cin >> filename;
    
        std::ofstream output_file(filename);
    
        for (int i = 0; i < count; i++)
        {
            shelter[i].increment_days_in_shelter();
            output_file << shelter[i].get_id() << " " << shelter[i].get_name() << " " << shelter[i].get_hair() << " " << shelter[i].get_color()
            << " " << shelter[i].get_days_in_shelter() << std::endl;
        }
        
        output_file.close();
        std::cout << "Saved " << count << " cats to " << filename << std::endl;
        
        return 0;
        
    }//end bracket fo first if statement
   
    /****************************
    End of Path A (File Input)
    *****************************/


    /****************************
    Path B for User To do regular input
    *****************************/

    if (input == "N" || input == "n")
    {
        for(int i = 0; i < NUM_CATS; i++)
        {


        //Instructions for the user to enter the pet's information

        std::cout << "Please enter the pet's name, hair type, and color or -1 to exit: " << std::endl;
        std::cout << "Name: ";
        std::cin >> new_name;
        if (new_name == "-1")
        {
            break;
        }
        std::cout << "Hair type: ";
        std::cin >> new_hair;
        std::cout << "Color: ";
        std::cin >> new_color;

        std::string new_id = generate_id(count);
        shelter[count] = Cat(new_name, new_hair, new_color, new_id);
        count++;
        
        }
    }
    
    std::cout << "Please enter the name of the file to write out: ";
    std::string second_file;
    std::cin >> second_file;

    std::ofstream output_file(second_file, std::ios::app);

    for (int i = 0; i < count; i++)
    {
        shelter[i].increment_days_in_shelter();
        output_file << shelter[i].get_id() << " " << shelter[i].get_name() << " " << shelter[i].get_hair() << " " 
        << shelter[i].get_color() << " " << shelter[i].get_days_in_shelter()  << std::endl;
    }

    output_file.close();
    std::cout << "Saved " << count << " cats to " << second_file << std::endl;
    //Breaking the loop after writing the data to the file
    
  
    //Returning 0 as the program ends successfully
    return 0;
}
    
    
