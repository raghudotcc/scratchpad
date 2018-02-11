/* Author@raghu
 * binary search function to iteratively search for an element in an array/vector
 * PRE-CONDN: array/vector must be sorted
 * RETURNS: postion of element if found, else return -1 
 */
int binary_search_recursive(std::vector<int> array,
                            int left_index, 
                            int right_index, 
                            int element_to_find
                            )
{
    if (right_index >= left_index) {

        int middle_index = left_index + (right_index - left_index) / 2;


        if (array[middle_index] == element_to_find) {       
            return middle_index;
        } 
        
        // if element in the middle index in the array id greater than the element_to_find
        // then, the element_to_find must be between lower_bound element and the middle_index element 
        if (array[middle_index] > element_to_find) {
            return binary_search_recursive(array, left_index, middle_index - 1, element_to_find);
        } 
        
        // if element in the middle index in the array id lesser than the element_to_find
        // then, the element_to_find must be between middle_index element and the higher_bound element
        return binary_search_recursive(array, middle_index + 1, right_index, element_to_find);
    }

    return -1;
}


/* binary search function to iteratively search for an element in an array/vector
 * PRE-CONDN: array/vector must be sorted
 * RETURNS: postion of element if found, else return -1 
 */
int binary_search_iterative(std::vector<int> array, 
                            int left_index, 
                            int right_index, 
                            int element_to_find
                            ) 
{

    while (right_index >= left_index) {
        int middle_index = left_index + (right_index - left_index) / 2;

        if (array[middle_index] == element_to_find) {
            return middle_index;
        }

        // if element in the middle index in the array id lesser than the element_to_find
        // then, the element_to_find must be between middle_index element and the higher_bound element
        if (array[middle_index] < element_to_find) {
            left_index = middle_index + 1;
        } else {
            // if element in the middle index in the array id greater than the element_to_find
            // then, the element_to_find must be between lower_bound element and the middle_index element 
            right_index = middle_index - 1;
        }
    }

    return -1;
}
