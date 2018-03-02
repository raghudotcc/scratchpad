/* Author@raghu
 * binary search function to iteratively search for an element in an array/vector
 * PRE-CONDN: array/vector must be sorted
 * RETURNS: postion of element if found, else return -1 
 */
int binary_search_recursive(std::vector<int> array,
                            int lower_bound, 
                            int upper_bound, 
                            int element_to_find
                            )
{
    if (upper_bound >= lower_bound) {

        int middle_index = lower_bound + (upper_bound - lower_bound) / 2;


        if (array[middle_index] == element_to_find) {       
            return middle_index;
        } 
        
        // if element in the middle index in the array id greater than the element_to_find
        // then, the element_to_find must be between lower_bound element and the middle_index element 
        if (array[middle_index] > element_to_find) {
            return binary_search_recursive(array, lower_bound, middle_index - 1, element_to_find);
        } 
        
        // if element in the middle index in the array id lesser than the element_to_find
        // then, the element_to_find must be between middle_index element and the higher_bound element
        return binary_search_recursive(array, middle_index + 1, upper_bound, element_to_find);
    }

    return -1;
}


/* binary search function to iteratively search for an element in an array/vector
 * PRE-CONDN: array/vector must be sorted
 * RETURNS: postion of element if found, else return -1 
 */
int binary_search_iterative(std::vector<int> array, 
                            int lower_bound, 
                            int upper_bound, 
                            int element_to_find
                            ) 
{

    while (upper_bound >= lower_bound) {
        int middle_index = lower_bound + (upper_bound - lower_bound) / 2;

        if (array[middle_index] == element_to_find) {
            return middle_index;
        }

        // if element in the middle index in the array id lesser than the element_to_find
        // then, the element_to_find must be between middle_index element and the higher_bound element
        if (array[middle_index] < element_to_find) {
            lower_bound = middle_index + 1;
        } else {
            // if element in the middle index in the array id greater than the element_to_find
            // then, the element_to_find must be between lower_bound element and the middle_index element 
            upper_bound = middle_index - 1;
        }
    }

    return -1;
}
