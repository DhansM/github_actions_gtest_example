#include <string>
#include <vector>
#include <numeric>
#include <regex>
#include <gtest/gtest.h>
using namespace std;
using namespace testing;

class StringCalculator {
public:
	int Add(const string &input);
};

class GetNegatives {
private:
	string negatives;

public:
	void operator()(int i) {
		if (i < 0)
			negatives.append(to_string(i) + ",");
	}

	operator string() {
		if (negatives.length() > 0)
			negatives.pop_back();

		return negatives;
	}
};

void check_for_negatives(const vector<int> &numbers) {
	string negatives = for_each(numbers.begin(), numbers.end(), GetNegatives());

	if (negatives.size() > 0) {
		throw invalid_argument("Negatives not allowed: " + negatives);
	}
}

void add_if_valid(vector<int> &numbers, string number_string) {
	int number = stoi(number_string);
	if (number <= 1000)
		numbers.push_back(number);
}

vector<int> get_numbers(const string &input) {
	regex numbers_only("(-?\\d+)+");

	vector<int> numbers;
	for_each(sregex_token_iterator(input.begin(), input.end(), numbers_only),
				sregex_token_iterator(),
				[&numbers](string s) { add_if_valid(numbers, s); });

	return numbers;
}

int StringCalculator::Add(const string &input) {
	if (input.empty())
		return 0;

	vector<int> numbers = get_numbers(input);

	check_for_negatives(numbers);

	return accumulate(numbers.begin(), numbers.end(), 0);
}

TEST(String_Calc_When_passed_a_single_number, returns_0_for_empty_string)
{
  StringCalculator testobj;
  string input="";
  int expecting_value = 0;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}


TEST(String_Calc_When_passed_a_single_number, returns_1_for_string_1)
{
  StringCalculator testobj;
  string input="1";
  int expecting_value = 1;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}

TEST(String_Calc_When_passed_a_single_number, returns_sum_of_num_for_string_1_2)
{
  StringCalculator testobj;
  string input="1","2";
  int expecting_value = 3;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}
