/* Author@raghu
 * function to find the given element in an array/vector using linear_scan_search 
 * RETURNS: postion of element if found, else return -1
 */
int linear_scan_search(std::vector<int> array, int element_to_find)
{
	for (int index = 0; index < array.size(); index++) {
		if (array[index] == element_to_find) {
			return index;
		}
	}

	return -1; // signifies that element was not found
}
