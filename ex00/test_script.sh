#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Check if AddressSanitizer is enabled
ASAN_ENABLED=0
if [ -f .asan_enabled ]; then
    ASAN_ENABLED=1
fi

# Run norminette check
echo "Running norminette check..."
output=$(norminette 2>&1)
if [ $? -ne 0 ]; then
	echo "$output" | grep -E --color=always "Error|Warning|Norme"
	echo -e "${RED}Norminette check failed${NC}"
#    exit 1
else
    echo -e "${GREEN}Norminette check passed${NC}"
fi

# Compile the files using make
echo "Compiling the program..."
#make > /dev/null 2> make_errors.log
make sanitize > /dev/null 2> make_errors.log
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed${NC}"
	cat make_errors.log
	rm -f make_errors.log
    exit 1
else
	rm -f make_errors.log
    echo -e "${GREEN}Compilation succeeded${NC}"
fi

# Function to generate a separator line of a given length
generate_separator() {
    local length=$1
    local separator=""
    for ((i=0; i<length; i++)); do
        separator="${separator}="
    done
    echo "$separator"
}

# Assign the longest test to a variable
longest_test="$> ./rush-02 numbers.dict 1000000000000000000000000000000000000 | cat -e"
# Add some padding for better visuals and generate the separator
separator=$(generate_separator $((${#longest_test} + 2)))

# Function to create test dictionaries
create_dictionaries() {
    echo "Creating invalid test dictionaries..."

    # Invalid dictionary: missing colon
    echo "1 one" > invalid_missing_colon.dict
    echo "2 two" >> invalid_missing_colon.dict

    # Invalid dictionary: non-numeric key
    echo "one : one" > invalid_non_numeric_key.dict
    echo "two : two" >> invalid_non_numeric_key.dict

    # Invalid dictionary: no value
    echo "1 :" > invalid_no_value.dict
    echo "2 :" >> invalid_no_value.dict

    # Invalid dictionary: leading spaces
    echo " 1 : one" > invalid_leading_spaces.dict
    echo " 2 : two" >> invalid_leading_spaces.dict

    echo "Creating special valid dictionary with spaces..."

    # Special valid dictionary with spaces
    echo "20  :   hey   everybody ! " > special_valid.dict

	echo -e "${GREEN}Test dictionaries created${NC}"
}

# Function to run a test and check the result
run_test() {
    local description=$1
    local dict=$2
    local value=$3
    local expected=$4

	echo "$separator"
	echo "$> ./rush-02 $dict $value | cat -e"

    # Create a temporary file
    temp_file=$(mktemp)
    # Run the command and redirect both stdout and stderr to the temporary file
    ./rush-02 $dict $value > "$temp_file" 2>&1
    output=$(cat "$temp_file" | cat -e)
    rm "$temp_file"

    if [ "$output" == "$expected" ]; then
		if [ -n "$ASAN_ENABLED" ] && [ "$ASAN_ENABLED" -eq 1 ] && [ -n "$asan_exit_code" ] && [ "$asan_exit_code" -ne 0 ]; then
            echo -e "${RED}Test failed due to AddressSanitizer errors${NC}"
            return 1
        else
            echo -e "${GREEN}Test passed${NC}"
			#echo -e "-> Actual output:\n$output"
            return 0
        fi
    else
        echo -e "${RED}Test failed${NC}"
        echo -e "-> Expected output:\n$expected"
        echo -e "-> Actual output:\n$output"
        return 1
    fi
}

# Create test dictionaries
create_dictionaries

# Run tests
all_tests_passed=true

# Valid tests
echo "$separator"
echo "-> Running valid tests..."
run_test "Valid number 0" "numbers.dict" "0" "zero$" || all_tests_passed=false
run_test "Valid number 00000000000" "numbers.dict" "00000000000" "zero$" || all_tests_passed=false
run_test "Valid number 1" "numbers.dict" "01" "one$" || all_tests_passed=false
run_test "Valid number 10" "numbers.dict" "10" "ten$" || all_tests_passed=false
run_test "Valid number 11" "numbers.dict" "11" "eleven$" || all_tests_passed=false
run_test "Valid number 14" "numbers.dict" "14" "fourteen$" || all_tests_passed=false
run_test "Valid number 15" "numbers.dict" "15" "fifteen$" || all_tests_passed=false
run_test "Valid number 16" "numbers.dict" "16" "sixteen$" || all_tests_passed=false
run_test "Valid number 17" "numbers.dict" "17" "seventeen$" || all_tests_passed=false
run_test "Valid number 18" "numbers.dict" "18" "eighteen$" || all_tests_passed=false
run_test "Valid number 19" "numbers.dict" "19" "nineteen$" || all_tests_passed=false
run_test "Valid number 20" "numbers.dict" "20" "twenty$" || all_tests_passed=false
run_test "Valid number 21" "numbers.dict" "21" "twenty one$" || all_tests_passed=false
run_test "Valid number 30" "numbers.dict" "30" "thirty$" || all_tests_passed=false
run_test "Valid number 40" "numbers.dict" "40" "forty$" || all_tests_passed=false
run_test "Valid number 50" "numbers.dict" "50" "fifty$" || all_tests_passed=false
run_test "Valid number 100" "numbers.dict" "100" "one hundred$" || all_tests_passed=false
run_test "Valid number 101" "numbers.dict" "101" "one hundred one$" || all_tests_passed=false
run_test "Valid number 110" "numbers.dict" "110" "one hundred ten$" || all_tests_passed=false
run_test "Valid number 111" "numbers.dict" "111" "one hundred eleven$" || all_tests_passed=false
run_test "Valid number 1000" "numbers.dict" "1000" "one thousand$" || all_tests_passed=false
run_test "Valid number 1001" "numbers.dict" "1001" "one thousand one$" || all_tests_passed=false
run_test "Valid number 1010" "numbers.dict" "1010" "one thousand ten$" || all_tests_passed=false
run_test "Valid number 1011" "numbers.dict" "1011" "one thousand eleven$" || all_tests_passed=false
run_test "Valid number 1100" "numbers.dict" "1100" "one thousand one hundred$" || all_tests_passed=false
run_test "Valid number 1101" "numbers.dict" "1101" "one thousand one hundred one$" || all_tests_passed=false
run_test "Valid number 1110" "numbers.dict" "1110" "one thousand one hundred ten$" || all_tests_passed=false
run_test "Valid number 1111" "numbers.dict" "1111" "one thousand one hundred eleven$" || all_tests_passed=false
run_test "Valid number 1000000" "numbers.dict" "1000000" "one million$" || all_tests_passed=false
run_test "Valid number 1000001" "numbers.dict" "1000001" "one million one$" || all_tests_passed=false
run_test "Valid number 1000010" "numbers.dict" "1000010" "one million ten$" || all_tests_passed=false
run_test "Valid number 1000011" "numbers.dict" "1000011" "one million eleven$" || all_tests_passed=false
run_test "Valid number 1000100" "numbers.dict" "1000100" "one million one hundred$" || all_tests_passed=false
run_test "Valid number 1000101" "numbers.dict" "1000101" "one million one hundred one$" || all_tests_passed=false
run_test "Valid number 1000110" "numbers.dict" "1000110" "one million one hundred ten$" || all_tests_passed=false
run_test "Valid number 1000111" "numbers.dict" "1000111" "one million one hundred eleven$" || all_tests_passed=false
run_test "Valid number 1001000" "numbers.dict" "1001000" "one million one thousand$" || all_tests_passed=false
run_test "Valid number 1001001" "numbers.dict" "1001001" "one million one thousand one$" || all_tests_passed=false
run_test "Valid number 1001010" "numbers.dict" "1001010" "one million one thousand ten$" || all_tests_passed=false
run_test "Valid number 1001011" "numbers.dict" "1001011" "one million one thousand eleven$" || all_tests_passed=false
run_test "Valid number 1001100" "numbers.dict" "1001100" "one million one thousand one hundred$" || all_tests_passed=false
run_test "Valid number 1001101" "numbers.dict" "1001101" "one million one thousand one hundred one$" || all_tests_passed=false
run_test "Valid number 1001110" "numbers.dict" "1001110" "one million one thousand one hundred ten$" || all_tests_passed=false
run_test "Valid number 1001111" "numbers.dict" "1001111" "one million one thousand one hundred eleven$" || all_tests_passed=false
run_test "Valid number 1000000000" "numbers.dict" "1000000000" "one billion$" || all_tests_passed=false
run_test "Valid number 1000000001" "numbers.dict" "1000000001" "one billion one$" || all_tests_passed=false
run_test "Valid number 1000000010" "numbers.dict" "1000000010" "one billion ten$" || all_tests_passed=false
run_test "Valid number 1000000011" "numbers.dict" "1000000011" "one billion eleven$" || all_tests_passed=false
run_test "Valid number 1000000100" "numbers.dict" "1000000100" "one billion one hundred$" || all_tests_passed=false
run_test "Valid number 1000000101" "numbers.dict" "1000000101" "one billion one hundred one$" || all_tests_passed=false
run_test "Valid number 1000000110" "numbers.dict" "1000000110" "one billion one hundred ten$" || all_tests_passed=false
run_test "Valid number 1000000111" "numbers.dict" "1000000111" "one billion one hundred eleven$" || all_tests_passed=false
run_test "Valid number 1000001000" "numbers.dict" "1000001000" "one billion one thousand$" || all_tests_passed=false
run_test "Valid number 1000001001" "numbers.dict" "1000001001" "one billion one thousand one$" || all_tests_passed=false
run_test "Valid number 1000001010" "numbers.dict" "1000001010" "one billion one thousand ten$" || all_tests_passed=false
run_test "Valid number 1000001011" "numbers.dict" "1000001011" "one billion one thousand eleven$" || all_tests_passed=false
run_test "Valid number 1000001100" "numbers.dict" "1000001100" "one billion one thousand one hundred$" || all_tests_passed=false
run_test "Valid number 1000001101" "numbers.dict" "1000001101" "one billion one thousand one hundred one$" || all_tests_passed=false
run_test "Valid number 1000001110" "numbers.dict" "1000001110" "one billion one thousand one hundred ten$" || all_tests_passed=false
run_test "Valid number 1000001111" "numbers.dict" "1000001111" "one billion one thousand one hundred eleven$" || all_tests_passed=false
run_test "Valid number 1000000000000" "numbers.dict" "1000000000000" "one trillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000" "numbers.dict" "1000000000000000" "one quadrillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000" "numbers.dict" "1000000000000000000" "one quintillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000000" "numbers.dict" "1000000000000000000000" "one sextillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000000000" "numbers.dict" "1000000000000000000000000" "one septillion$" || all_tests_passed=false
run_test "Valid number 10000000000000005000000000" "numbers.dict" "10000000000000005000000000" "ten septillion five billion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000000000000" "numbers.dict" "1000000000000000000000000000" "one octillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000000000000000" "numbers.dict" "1000000000000000000000000000000" "one nonillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000000000000000000" "numbers.dict" "1000000000000000000000000000000000" "one decillion$" || all_tests_passed=false
run_test "Valid number 1000000000000000000000000000000000000" "numbers.dict" "1000000000000000000000000000000000000" "one undecillion$" || all_tests_passed=false

# Valid test with special dictionary
echo "$separator"
echo "-> Running valid test with special dictionary..."
run_test "Valid number 20 with special dictionary" "special_valid.dict" "20" "hey everybody !$" || all_tests_passed=false

# Invalid tests
echo "$separator"
echo "-> Running invalid tests..."
run_test "Invalid number 10.4" "numbers.dict" "10.4" "Error$" || all_tests_passed=false
run_test "Invalid dictionary: missing colon" "invalid_missing_colon.dict" "1" "Dict Error$" || all_tests_passed=false
run_test "Invalid dictionary: non-numeric key" "invalid_non_numeric_key.dict" "1" "Dict Error$" || all_tests_passed=false
run_test "Invalid dictionary: no value" "invalid_no_value.dict" "1" "Dict Error$" || all_tests_passed=false
run_test "Invalid dictionary: leading spaces" "invalid_leading_spaces.dict" "1" "Dict Error$" || all_tests_passed=false

# Final result
echo "$separator"
if $all_tests_passed; then
    echo -e "${GREEN}All tests passed: OK${NC}"
else
    echo -e "${RED}Some tests failed: KO${NC}"
fi
echo "$separator"

# Clean up compiled files and dictionaries
make fclean > /dev/null 2>&1
rm invalid_missing_colon.dict invalid_non_numeric_key.dict invalid_no_value.dict invalid_leading_spaces.dict special_valid.dict

if [ -f .asan_enabled ]; then
	rm -f .asan_enabled
fi
