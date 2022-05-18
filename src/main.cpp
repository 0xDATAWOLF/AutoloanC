/**
 * Calculates the cost of an auto loan based on the information supplied by the user.
 * 
 * TODO:
 * 1.	Standard-output formatting.
 * 2.	Output to text file.
 * 3.	Output to CSV.
 * 4.	Input validation (ensure numbers are represented as they should be, no bad input)
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <ctype.h>
#include <unordered_map>
#include <stdlib.h>
#include <assert.h>

#include "./datatable.h"

#define DEBUG_MODE 0

#define internal static
#define global static
#define lpersist static

typedef struct
{
	union
	{
		struct
		{
			double balance;
			double apr;
			double term;
		};
		double _params[3];
	};
	std::unordered_map<std::string, double> parameters;
} finance_params;

void showHelpHelp(std::string = "");
bool validateHelp(int, char**);
bool validateFinanceParameters(finance_params*, int, char**);
double calculateMonthlyPayment(double, double, int);
double calculateMonthlyPayment(finance_params, int = 0);

int
main(int argc, char** argv)
{

	// Display help as needed, fast-exit condition.
	if (validateHelp(argc, argv)) return 0;

	// Validate input parameters, if invalid, show the help message.
	finance_params fParams = {};
	if (!validateFinanceParameters(&fParams, argc, argv))
		showHelpHelp("Please check your input and try again.");

	// Create a data table and initialize the column headers.
	data_table<4> loanTable;
	loanTable.set_headers({"Amount Financed", "Interest Paid", "Monthly Payment", "Term Length"});

	// Now build the table using term lengths.
	for (int termLength = (int)fParams.term; termLength > 0; termLength -= 12)
	{
		double m = calculateMonthlyPayment(fParams, termLength);
		double tloan = m*termLength;
		double idiff = tloan - fParams.balance;
		loanTable.push_row({std::to_string(tloan), std::to_string(idiff), std::to_string(m), std::to_string(termLength)});
	}

	// Print the table to the user.
	std::cout << loanTable.build_ascii() << std::endl;

	return 0;

}

/**
 * Display the help dialogue as needed and catches no-input on the command line.
 * The return value determines if the help dialogue was printed. The program should
 * fast-close if the value is true.
 */
internal inline bool
validateHelp(int argc, char** argv)
{

#if DEBUG_MODE
	for (int i = 0; i < argc; ++i) std::cout << "ARGV[" << i << "] " << argv[i] << std::endl;
#endif

	if (argc == 1)
	{
		showHelpHelp();
		return true; // Fast exit, enforce useage of -h/--help in the command line.
	}

	// Since argc is valid (greater than one) and the following commands aren't help
	// commands, we can fast-exit here and continue processing user input.
	if (!(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) return false;

	// Display help.
	std::cout << "Autoloanc - A simple and fast auto loan calculator.\n";
	std::cout << "Developed by Chris DeJong | 0xDATAWOLF, May 2022.\n\n";

	std::cout << "Supply the loan balance, annual percentage rate, and loan term as command line arguments.\n";
	std::cout << "Providing these values will not take into consideration the tax rate, additional fees, trade-in,\n";
	std::cout << "or down payment. These parameters can be provided as optional parameters to the calculation\n";
	std::cout << "by using their appropriate flags as listed below. Otherwise, incorporate these parameters into the\n";
	std::cout << "balance prior to running the program.\n\n";

	std::cout << "Example useage: autoloanc 25000.00 2.9 48\n\n";

	std::cout << std::left;
	std::cout << std::setw(32) << "--help, -h";
	std::cout << std::setw(128) << "Produces the help menu with a list of commands and their useage.";

	return true;	

}

/**
 * Validates the finance parameters and returns true if it was properly validated.
 * This function takes a finance_params struct pointer to be filled out (if successful).
 */
internal bool
validateFinanceParameters(finance_params* parameters, int argc, char** argv)
{

	if (argc < 4) return false; // There is a minimum requirement of 4 arguments. Fast-exit.

	for (int i = 1; i < 4; ++i)
		parameters->_params[i-1] = atof(argv[i]);

	return true;

}

/**
 * Prints the help message.
 */
internal inline void
showHelpHelp(std::string reason)
{
	if (reason != "") std::cout << reason << std::endl;
	std::cout << "Use -h or --help for additional information on how to use this program.\n";
}

/**
 * An overloaded function alias which takes finance_params and an alt_term as arguments.
 */
internal inline double
calculateMonthlyPayment(finance_params fParams, int alt_term)
{
	// Forward to the proper function.
	return calculateMonthlyPayment(fParams.balance, fParams.apr,
		(alt_term > 0) ? alt_term : (int)fParams.term);
}

/**
 * Calculuates the monthly payment based on a loan balance, APR, and term length.
 */
internal double
calculateMonthlyPayment(double bal, double apr, int term)
{
	double rpm = apr / 12.0;
	double a = rpm * pow(1 + rpm, term);
	double b = pow(1 + rpm, term) - 1;
	double monthly = bal * (a / b);
	return monthly;
}
