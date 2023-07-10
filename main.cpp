#include <iostream>
#include <string>

struct Node
{
	std::string pcn,
				last_name,
				given_name,
				middle_name,
				birthdate,
				sex,
				marital_status,
				blood_type,
				nationality,
				date_of_issue,
				email_address,
				home_address,
				tag;
	Node* next{};
};

class Profile
{
	Node* head, * tail;

public:
	Profile() : head(nullptr), tail(nullptr) {}

	void add_profile
	(
		std::string pcn,
		std::string last_name,
		std::string given_name,
		std::string middle_name,
		std::string birthdate,
		std::string sex,
		std::string marital_status,
		std::string blood_type,
		std::string nationality,
		std::string date_of_issue,
		std::string email_address,
		std::string home_address,
		std::string tag
	)
	{
		// NOTE: std::ws is a manipulator that ignores whitespaces in a string sequence
		std::cout << "Enter PCN (Ex. xxxx-xxxx-xxxx-xxxx): ";
		std::getline(std::cin >> std::ws, pcn);
		std::cout << "Enter Last Name: ";
		std::getline(std::cin >> std::ws, last_name);
		std::cout << "Enter Given Name: ";
		std::getline(std::cin >> std::ws, given_name);
		std::cout << "Enter Middle Name: ";
		std::getline(std::cin >> std::ws, middle_name);
		std::cout << "Enter Birthdate (Ex. mm/dd/yyyy): ";
		std::getline(std::cin >> std::ws, birthdate);
		std::cout << "Enter Sex (Ex. Male/Female): ";
		std::getline(std::cin >> std::ws, sex);
		std::cout << "Enter Marital Status (Ex. Single/Married): ";
		std::getline(std::cin >> std::ws, marital_status);
		std::cout << "Enter Blood Type (Ex. O+): ";
		std::getline(std::cin >> std::ws, blood_type);
		std::cout << "Enter Nationality (Ex. Filipino): ";
		std::getline(std::cin >> std::ws, nationality);
		std::cout << "Enter Date of Issue: ";
		std::getline(std::cin >> std::ws, date_of_issue);
		std::cout << "Enter Email Address (Ex. juandelacruz@gmail.com): ";
		std::getline(std::cin >> std::ws, email_address);
		std::cout << "Enter Home Address: ";
		std::getline(std::cin >> std::ws, home_address);
		std::cout << "Enter Tag (Positive or Negative): ";
		std::getline(std::cin >> std::ws, tag);
		
		Node* new_profile_1 = new Node;
		new_profile_1->pcn= pcn;
		new_profile_1->last_name = last_name;
		new_profile_1->given_name = given_name;
		new_profile_1->middle_name = middle_name;
		new_profile_1->birthdate = birthdate;
		new_profile_1->sex = sex;
		new_profile_1->marital_status = marital_status;
		new_profile_1->blood_type = blood_type;
		new_profile_1->nationality = nationality;
		new_profile_1->date_of_issue = date_of_issue;
		new_profile_1->email_address = email_address;
		new_profile_1->home_address = home_address;
		new_profile_1->tag = tag;
		new_profile_1->next = nullptr;

		if (head == nullptr)
			head = new_profile_1;
		else
		{
			Node* new_profile_2 = head;

			while (new_profile_2->next != nullptr)
				new_profile_2 = new_profile_2->next;

			new_profile_2->next = new_profile_1;
		}
	}

	void delete_profile(std::string pcn)
	{
		std::cout << "Enter the PCN of the profile you want to delete: ";
		std::cin >> pcn;

		Node* current = head;
		Node* previous = nullptr;

		if (current == nullptr)
		{
			std::cout << "No profile exists... " << std::endl;
			return;
		}
		else
		{
			while (current != nullptr)
			{
				if (current->pcn == pcn)
				{
					if (previous == nullptr)
					{
						head = current->next;
						delete current;
						current = head;

					}
					else
					{
						previous->next = current->next;
						delete current;
						current = previous->next;
					}
				}
				else
				{
					previous = current;
					current = current->next;

					if (current == nullptr)
					{
						std::cout << "The PCN does not exist... " << std::endl;
						return;
					}
				}
			}

			std::cout << "The profile with PCN: " << pcn << " is successfully deleted" << std::endl << std::endl;
		}
	}

	void display()
	{
		std::cout << "Displaying all profile..." << std::endl << std::endl;

		Node* profile = head;

		if (profile == nullptr)
		{
			std::cout << "No Profile/s found..." << std::endl << std::endl;
			return;
		}

		while (profile != nullptr)
		{
			std::cout << "PCN: " << profile->pcn << std::endl;
			std::cout << "Full name: " << profile->last_name << ", " << profile->given_name << " " << profile->middle_name << std::endl;
			std::cout << "Birthdate: " << profile->birthdate << std::endl;
			std::cout << "Sex: " << profile->sex << std::endl;
			std::cout << "Marital Status: " << profile->marital_status << std::endl;
			std::cout << "Blood Type: " << profile->blood_type << std::endl;
			std::cout << "Nationality:  " << profile->nationality << std::endl;
			std::cout << "Date of Issue: " << profile->date_of_issue << std::endl;
			std::cout << "Email Address: " << profile->email_address << std::endl;
			std::cout << "Tag: " << profile->tag << std::endl;
			profile = profile->next;
		}

		std::cout << std::endl << std::endl;
	}

	void search(std::string pcn)
	{
		std::cout << "Enter the PCN of the profile you want to search: ";
		std::cin >> pcn;
		std::cout << std::endl;

		Node* current = head;
		Node* previous = nullptr;

		if (current == nullptr)
		{
			std::cout << "No profile/s found3..." << std::endl;
			return;
		}
		else
		{
			while (current != nullptr)
			{
				if (current->pcn == pcn)
				{
					previous = current;
					std::cout << "PCN: " << current->pcn << std::endl;
					std::cout << "Full name: " << current->last_name << ", " << current->given_name << " " << current->middle_name << std::endl;
					std::cout << "Birthdate: " << current->birthdate << std::endl;
					std::cout << "Sex: " << current->sex << std::endl;
					std::cout << "Marital Status: " << current->marital_status << std::endl;
					std::cout << "Blood Type: " << current->blood_type << std::endl;
					std::cout << "Nationality:  " << current->nationality << std::endl;
					std::cout << "Date of Issue: " << current->date_of_issue << std::endl;
					std::cout << "Email Address: " << current->email_address << std::endl;
					std::cout << "Tag: " << current->tag << std::endl;
					current = current->next;
				}
				else
				{
					previous = current;
					current = current->next;

					if (current == nullptr)
					{
						std::cout << "The PCN does not exist... " << std::endl;
						return;
					}
				}
			}
		}
		std::cout << std::endl;
	}

	
};

int main()
{
	Profile profile;
	std::string pcn,
				last_name,
				given_name,
				middle_name,
				birthdate,
				sex,
				marital_status,
				blood_type,
				nationality,
				date_of_issue,
				email_address,
				home_address,
				tag;
	int choice{};

	do
	{
		system("cls");
		std::cout << "PROFILE ADD/DELETE/DISPLAY/SEARCH" << std::endl << std::endl;
		std::cout << "[1] ADD PROFILE" << std::endl;
		std::cout << "[2] DELETE PROFILE" << std::endl;
		std::cout << "[3] DISPLAY ALL PROFILE" << std::endl;
		std::cout << "[4] SEARCH PROFILE" << std::endl;
		std::cout << "[5] EXIT PROGRAM" << std::endl << std::endl;
		std::cout << "ENTER CHOICE (1-5): ";
		std::cin >> choice;

		while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "ENTER CHOICE (1-5): ";
			std::cin >> choice;
		}

		system("cls");

		if (choice == 1)
		{
			profile.add_profile
			(
				pcn,
				last_name,
				given_name,
				middle_name,
				birthdate,
				sex,
				marital_status,
				blood_type,
				nationality,
				date_of_issue,
				email_address,
				home_address,
				tag
			);
		}
		else if (choice == 2)
			profile.delete_profile(pcn);
		else if (choice == 3)
			profile.display();
		else if (choice == 4)
			profile.search(pcn);

		system("pause");
	} while (choice != 5);
	
	std::cout << "Exiting Program..." << std::endl << std::endl;
	return 0;
}