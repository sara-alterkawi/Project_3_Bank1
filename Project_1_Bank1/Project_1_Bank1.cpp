// Write a C++ program that displays a menu for managing clients in a banking application.
// The menu should include options to show the client list,
// add a new client, delete a client,
// update client information,
// find a client,
// and exit the program.
// Each option should be numbered from 1 to 6.
// ============================================================
//					Main Menue Screen
// ============================================================
//			[1] Show Client List.
//			[2] Add New Client.
//			[3] Delete Client.
//			[4] Update Client Info.
//			[5] Find Client.
//			[6] Exit.
// ============================================================
// Choose what do you want to do? [1 to 6]?
// When the user selects an option, the program should display a message indicating which option was selected.
// and press any key to return to the main menu.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
void ShowMainMenu();

// Define the structure to hold client data
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

// Function to split a string into words based on a delimiter
vector<string> SplitString(string str, string delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = str.find(delim)) != std::string::npos)
	{
		sWord = str.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		str.erase(0, pos + delim.length());  /* erase() until positon and move to next word. */
	}
	if (str != "")
	{
		vString.push_back(str); // it adds last word of the string.
	}
	return vString;
}

// Function to convert client data to a single line string
sClient ConvertLineToRecord(string line, string separator = "#//#")
{
	sClient client;
	vector<string> vClientData = SplitString(line, separator);
	client.AccountNumber = vClientData[0];
	client.PinCode = vClientData[1];
	client.Name = vClientData[2];
	client.Phone = vClientData[3];
	client.AccountBalance = stod(vClientData[4]);
	return client;
}

// Function to convert record to line
string ConvertClientDataToLine(const sClient& client, string separator = "#//#")
{
	return client.AccountNumber + separator +
		client.PinCode + separator +
		client.Name + separator +
		client.Phone + separator +
		to_string(client.AccountBalance);
}

// Function to check if client exists by AccountNumber
bool ClientExistsByAccountNumber(string accountNumber, string fileName)
{
	vector <sClient> vClients;
	fstream myFile;
	myFile.open(fileName, ios::in);//read Mode
	if (myFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(myFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber ==accountNumber)
			{
				myFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		myFile.close();
	}
	return false;
}

// Function to add a new client
sClient ReadNewClient()
{
	sClient client;
	cout << "Enter Account Number? ";
	getline(cin >> ws, client.AccountNumber);

	while (ClientExistsByAccountNumber(client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, client.PinCode);

	cout << "Enter Name? ";
	getline(cin, client.Name);

	cout << "Enter Phone? ";
	getline(cin, client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> client.AccountBalance;

	return client;
}

// Function to load clients from file
vector <sClient> LoadCleintsDataFromFile(string fileName)
{
	vector <sClient> vClients;
	fstream myFile;
	myFile.open(fileName, ios::in);//read Mode
	if (myFile.is_open())
	{
		string line;
		sClient client;
		while (getline(myFile, line))
		{
			client = ConvertLineToRecord(line);
			vClients.push_back(client);
		}
		myFile.close();
	}
	return vClients;
}

// Function to print client data
void PrintClientRecordLine(sClient client)
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "| " << setw(15) << left << client.AccountNumber;
	cout << "| " << setw(10) << left << client.PinCode;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " << setw(12) << left << client.Phone;
	cout << "| " << setw(12) << left << client.AccountBalance;
}

// Function to print all clients
void PrintAllClients(vector <sClient> vClients)
{
	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "| " << setw(15) << left << "Accout Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;

	for (sClient client : vClients)
	{
		PrintClientRecordLine(client);
		cout << endl;
	}
	cout << "----------------------------------------------------------------------------------------" << endl;
}

// Function to print client data
void PrintClientRecord(sClient client)
{
	cout << "\nThe following is the extracted client record:\n";
	cout << "----------------------------------------\n";
	cout << "Account Number\t: " << client.AccountNumber << endl;
	cout << "Pin Code\t: " << client.PinCode << endl;
	cout << "Name\t\t: " << client.Name << endl;
	cout << "Phone\t\t: " << client.Phone << endl;
	cout << "Account Balance\t: " << client.AccountBalance << endl;
	cout << "----------------------------------------\n";
}

// Function to find and print client by AccountNumber
bool FindClientByAccountNumber(string accountNumber, vector<sClient> vClients, sClient& client)
{
	for (sClient c : vClients)
	{
		if (c.AccountNumber == accountNumber)
		{
			client = c;
			return true;
		}
	}
	return false;
}

// Function to change client record
sClient ChangeClientRecord(string accountNumber)
{
	sClient client;
	client.AccountNumber = accountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, client.PinCode);

	cout << "Enter Name? ";
	getline(cin, client.Name);

	cout << "Enter Phone? ";
	getline(cin, client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> client.AccountBalance;

	return client;
}

// Function to mark client for delete by AccountNumber
bool MarkClientForDeleteByAccountNumber(string accountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == accountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

// Function to save clients to file
vector <sClient> SaveCleintsDataToFile(string fileName, vector <sClient> vClients)
{
	fstream myFile;
	myFile.open(fileName, ios::out);
	string dataLine;

	if (myFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				dataLine = ConvertClientDataToLine(C);
				myFile << dataLine << endl;
			}
		}

		myFile.close();
	}
	return vClients;
}

// Function to add data line to file
void AddDataLineToFile(string fileName, string stDataLine)
{
	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);
	if (myFile.is_open())
	{
		myFile << stDataLine << endl;
		myFile.close();
	}
}

// Function to add new client
void AddNewClient()
{
	sClient client = ::ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertClientDataToLine(client));
}

// Function to add multiple new clients
void AddNewClients()
{
	char answer = 'Y';
	do
	{
		//system("cls");
		cout <<"Adding New Client:\n\n";
		AddNewClient();
		cout <<"\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> answer;
	}while (toupper(answer) == 'Y');
}

// Function to delete client by AccountNumber
bool DeleteByAccountNumber(string accountNumber, vector<sClient>& vClients)
{
	sClient client;
	char answer = 'n';
	if (FindClientByAccountNumber(accountNumber, vClients, client))
	{
		PrintClientRecord(client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(accountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients); //Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully." << endl;
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
		return false;
	}
}

// Function to delete client by AccountNumber
bool UpdateClientByAccountNumber(string accountNumber, vector<sClient>& vClients)
{
	sClient client;
	char answer = 'n';
	if (FindClientByAccountNumber(accountNumber, vClients, client))
	{
		PrintClientRecord(client);
		cout << "\n\nAre you sure you want update  this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == accountNumber)
				{
					C = ChangeClientRecord(accountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!\n";
		return false;
	}
}

// function to read AccountNumber from user and print client details
string ReadAccountNumberFromUser()
{
	string accountNumber;
	cout << "Please enter AccountNumber? ";
	cin >> accountNumber;
	return accountNumber;
}

// Function to show delete client screen
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string accountNumber = ReadAccountNumberFromUser();
	DeleteByAccountNumber(accountNumber, vClients);
}

// Function to show delete client screen
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string accountNumber = ReadAccountNumberFromUser();
	UpdateClientByAccountNumber(accountNumber, vClients);
}

// Function to show add new clients screen
void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";
	AddNewClients();
}

// Function to show find client screen
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient client;
	string accountNumber = ReadAccountNumberFromUser();
	if (FindClientByAccountNumber(accountNumber, vClients, client))
		PrintClientRecord(client);
	else
		cout << "\nClient with Account Number[" << accountNumber << "] is not found!";
}

// Function to show end screen
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

// Enum for main menu options
enum enMainMenueOptions
{
	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eExit = 6
};

// Function to prompt user to press any key to continue
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	system("cls");
	ShowMainMenu();
}

// Function to read main menu option
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short choice = 0;
	cin >> choice;
	return choice;
}

// Function to handle user choices
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
	{
		system("cls");
		vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
		PrintAllClients(vClients);
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

// Function to display the main menu
void ShowMainMenu()
{
	cout << "===========================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

// Main function
int main()
{
	ShowMainMenu();
	system("pause>0");
	return 0;
}