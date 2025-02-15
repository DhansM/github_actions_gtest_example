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

//Fixture
class String_Calc:public TestWithParam<std::tuple<string,int>>{
protected: 
//Arrange
StringCalculator testobj;
};

TEST_P(String_Calc,Assert_add_operation_all_testcases)
{
	const std::tuple<string,int> & parameter = GetParam();
	string input = std::get<0>(parameter);
	int expected_value = std::get<1>(parameter);
        int actual_value = testobj.Add(input);
	ASSERT_EQ(actual_value,expected_value);
}

INSTANTIATE_TEST_SUITE_P(String_Calc_Param_test,
	String_Calc,
	Values(
	std::make_tuple("",0),
	std::make_tuple("1",1),
	std::make_tuple("1,2",3),
	std::make_tuple("1,2,3",6)
	));

/*TEST_F(String_Calc,When_passed_a_single_number_returns_0_for_empty_string)
{
  //StringCalculator testobj;
  string input="";
  int expecting_value = 0;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}*/


/*TEST_F(String_Calc,When_passed_a_single_number_returns_1_for_string_1)
{
  //StringCalculator testobj;
  string input="1";
  int expecting_value = 1;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}*/

/*TEST_F(String_Calc,When_passed_a_single_number_returns_sum_of_num_for_string_1_2)
{
  //StringCalculator testobj;
  string input="1,2";
  int expecting_value = 3;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}*/


/*TEST_F(String_Calc,When_passed_a_multiple_numbers_returns_sum_of_num_for_string_1_2_3)
{
  //StringCalculator testobj;
  string input="1,2,3";
  int expecting_value = 6;
 //act
  int actualvalue = testobj.Add(input);
  // assert
  ASSERT_EQ(actualvalue,expecting_value);	
	
}*/

bool isEven(int number) {return number%2==0; }

class Even_Test_Suite:public TestWithParam<int>{
};

TEST_P(Even_Test_Suite, Assert_For_Even_Numbers)
{
  int input = GetParam();
  bool expected_result = true;
  bool actual_result = isEven(input);
  ASSERT_EQ(expected_result,actual_result);
}

INSTANTIATE_TEST_SUITE_P(IsEvenParamExample,
	Even_Test_Suite,
	Values(16,28,2,4,6,8));
