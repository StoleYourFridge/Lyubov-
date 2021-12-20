#include <vector>
#include <iostream>

using namespace std;

class GeometricVector
{
private:
	double x = 0, y = 0, z = 0;
public:
	GeometricVector();
	GeometricVector(double x, double y, double z);
	double get_modulus();
	bool operator>(GeometricVector& comparing);
	friend ostream& operator<<(ostream& stream, const GeometricVector vect);
};

// std::vector<int> bubble_sort(std::vector<int> input_arr);
// std::vector<int> bucket_sort(std::vector<int> input_arr, int bucket_quantity);

template <typename T> std::vector<T> bubble_sort(std::vector<T> input_arr)
{
	int changes;
	do
	{
		changes = 0;
		for (int i = 0; i < input_arr.size() - 1; i++)
		{
			if (input_arr[i] > input_arr[i + 1])
			{
				T dummy = input_arr[i];
				input_arr[i] = input_arr[i + 1];
				input_arr[i + 1] = dummy;
				changes++;
			}
		}
	} while (changes > 0);
	return input_arr;
}

template <typename T> std::vector<T> bucket_sort(std::vector<T> input_arr, int bucket_quantity)
{
	int interval_size = input_arr.size() / bucket_quantity; // determines the length of the range that each bucket covers, in case of equal distribution - just the size of a bucket
	if (input_arr.size() % bucket_quantity != 0) bucket_quantity++; // if the size of the input array is not a multiple of needed bucket quantity, we need one more buckets to account for the elements at the end of the array
	int last_interval_starting_point = bucket_quantity * (interval_size - 1) - 1; // these two variables are needed for the case when the above condition worked; they determine the range of the last interval
	int last_interval_ending_point = input_arr.size() - 1; // it will start at the end of the next-to-last interval and end at the last index of the array, since no element can be bigger than more elements than there are in the array
	std::vector<int> greater_quantities; // will store the number of elements that are less than the current element in the array, index-wise
	for (int i = 0; i < input_arr.size(); i++) greater_quantities.push_back(0); // initialization
	for (int curr_element_ind = 0; curr_element_ind < input_arr.size(); curr_element_ind++)
	{
		for (int curr_possible_smaller_element_ind = 0; curr_possible_smaller_element_ind < input_arr.size(); curr_possible_smaller_element_ind++)
		{
			if (input_arr[curr_element_ind] > input_arr[curr_possible_smaller_element_ind]) greater_quantities[curr_element_ind]++;
		}
	}
	std::vector<std::vector<T>> buckets;
	for (int i = 0; i < bucket_quantity; i++) buckets.push_back({}); // initialization
	for (int curr_element_ind = 0; curr_element_ind < input_arr.size(); curr_element_ind++)
	{
		int curr_greater_quantity = greater_quantities[curr_element_ind];
		for (int curr_bucket_ind = 0; curr_bucket_ind < bucket_quantity; curr_bucket_ind++)
		{
			if (curr_bucket_ind == bucket_quantity - 1) // this condition will pass with any number of needed buckets, but will behave the same as the below condition if the number of buckets is a multiple of input array size
			{
				if (curr_greater_quantity >= last_interval_starting_point && curr_greater_quantity <= last_interval_ending_point)
				{
					buckets[curr_bucket_ind].push_back(input_arr[curr_element_ind]);
				}
			}
			else if (curr_greater_quantity >= curr_bucket_ind * interval_size && curr_greater_quantity <= (curr_bucket_ind + 1) * interval_size) // the elements are distributed between buckets based on their respective values in greater_quantities
			{
				buckets[curr_bucket_ind].push_back(input_arr[curr_element_ind]); // pushing the element to its respective bucket based on how many elements in the input array are less than the element
				break;
			}
		}
	}

	std::vector<T> result;
	for (int curr_bucket_ind = 0; curr_bucket_ind < bucket_quantity; curr_bucket_ind++)
	{
		if (buckets[curr_bucket_ind].size() == 0) continue;
		buckets[curr_bucket_ind] = bubble_sort(buckets[curr_bucket_ind]); // then each bucket is sorted individually
		for (int curr_el_ind = 0; curr_el_ind < buckets[curr_bucket_ind].size(); curr_el_ind++)
		{
			result.push_back(buckets[curr_bucket_ind][curr_el_ind]); // and all their entries are connected in one vector
		}
	}
	return result;
}

template <typename T> void selection_sort(std::vector<T>& input_arr)
{
	T curr_min;
	int curr_min_index = 0;
	int curr_first_unsorted_element_index = 0;
	bool change_made;
	while(curr_first_unsorted_element_index < input_arr.size()) // could've been a for cycle, but this is more semantic i believe
	{
		change_made = false;
		curr_min = input_arr[curr_first_unsorted_element_index]; // setting the current minimal element to be the first unsorted element
		for (int i = curr_first_unsorted_element_index; i < input_arr.size(); i++) // we only need to check the unsorted part
		{
			if (curr_min > input_arr[i]) // just the default algorithm of finding the minimal element in an array
			{
				curr_min = input_arr[i];
				curr_min_index = i;
				change_made = true;
			}
		}
		if (!change_made) // aka the first unsorted element was the minimal one, and no swap needs to happen
		{
			curr_first_unsorted_element_index++;
		}
		else // aka the minimal element is somewhere inside the unsorted part of the array, so a swap needs to happen
		{
			T dummy = input_arr[curr_first_unsorted_element_index]; // nothing special here
			input_arr[curr_first_unsorted_element_index] = curr_min;
			input_arr[curr_min_index] = dummy;
			curr_first_unsorted_element_index++;
		}
	} 	
}