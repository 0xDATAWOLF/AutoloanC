#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <array>
#include <string>
#include <sstream>

/** Define the data_table defaults. */
#define MIN_COLUMN_SIZING 16
#define MIN_COLUMN_GUTTER 4
#define ROW_SPACER_TOKEN "-"
#define COLUMN_DIVIDER_TOKEN " | "

/**
 * The data table class contains the necessary information to construct a table of
 * data in ASCII using given information. The table can be moderately customized to
 * display data as needed.
 */
template<int cols>
class data_table
{
	public:
		void set_header(int index, std::string title) { _table_headers[index] = title; };
		void set_headers(std::array<std::string, cols> headers) { _table_headers = headers; };
		void push_row(std::array<std::string, cols> row) { _table_rows.push_back(row); };

		std::string build_ascii();

	private:
		std::array<std::string, cols> _table_headers;
		std::vector<std::array<std::string, cols>> _table_rows;
};

/**
 * As the name suggests, this function builds the table using the supplied data in ASCII.
 * The output of this function is a string, ready for printing.
 */
template<int cols> std::string data_table<cols>::
build_ascii()
{

	// Determine the maximum column size needed. The default size is determined by a macro,
	// and if any of the subsequent rows or headers are larger, we will adjust the maximum to
	// accomodate that size.
	int maximumColumnSizing = MIN_COLUMN_SIZING + MIN_COLUMN_GUTTER;
	for (int r = -1; r < (int)_table_rows.size(); ++r)
	{

		// Do the headers first.
		if (r < 0)
		{
			for (int c = 0; c < cols; ++c)
			{
				int slen = _table_headers[c].length();
				if (slen > maximumColumnSizing)
					maximumColumnSizing = (slen + MIN_COLUMN_GUTTER);
			}
		}

		// Then do the rows.
		else
		{
			for (int c = 0; c < cols; ++c)
			{
				int slen = _table_rows[r][c].length();
				if (slen > maximumColumnSizing)
					maximumColumnSizing = (slen + MIN_COLUMN_SIZING);
			}
		}
	}

	// With the maximum calulated, we can now format the table with the information provided.
	std::stringstream tstream;

	// Calculate the seperator width.
	int sepCount = (maximumColumnSizing*cols)+((cols)*strlen(COLUMN_DIVIDER_TOKEN))+strlen(COLUMN_DIVIDER_TOKEN);

	// Top of the table.
	for (int i = 0; i < sepCount; ++i) tstream << ROW_SPACER_TOKEN; tstream << std::endl;

	// Header row.
	tstream << COLUMN_DIVIDER_TOKEN; // Left side divider token to make a box.
	for (int c = 0; c < cols; ++c)
	{
		// Store a temp string stream and calculate the offset necessary to center the text.
		std::stringstream temp;
		int centerSpacingCount = ( maximumColumnSizing - _table_headers[c].length() ) / 2;
		for (int i = 0; i < centerSpacingCount; ++i) temp << " ";
		temp << _table_headers[c];
		
		// Append and insert divider.
		tstream << std::setw(maximumColumnSizing) << std::left << temp.str() << COLUMN_DIVIDER_TOKEN;

	}
	tstream << std::endl;
	for (int i = 0; i < sepCount; ++i) tstream << ROW_SPACER_TOKEN; tstream << std::endl;

	// Procedurally create each row within the table.
	for (unsigned int r = 0; r < _table_rows.size(); ++r)
	{
		tstream << COLUMN_DIVIDER_TOKEN;
		for (int c = 0; c < cols; ++c)
		{
			tstream << std::right << std::setw(maximumColumnSizing) << _table_rows[r][c] << COLUMN_DIVIDER_TOKEN;
		}
		tstream << "\n";
	}

	// Bottom of the table.
	for (int i = 0; i < sepCount; ++i) tstream << ROW_SPACER_TOKEN; tstream << std::endl;

	return tstream.str();

}

#endif