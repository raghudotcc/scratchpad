/* Author@raghu
 * quick sort function to recursively sort the elements in array/vector
 * this function picks last element as pivot for ease
 * POST-CONDN: array/vector must be sorted in ascending order
 * RETURNS: void does not return anything
 */
void quick_sort(std::vector<int> &array, int lower_bound, int upper_bound)
{
    if (upper_bound > lower_bound) {
        int pivot_index = point_of_partition(array, lower_bound, upper_bound);

        quick_sort(array, lower_bound, pivot_index - 1);
        quick_sort(array, pivot_index + 1, upper_bound);
    }
}

/* partions array and returns pivot point
 * RETURNS: pivot index
 */
int point_of_partition(std::vector<int> &array, 
                       int lower_bound, 
                       int upper_bound
                       )
{
    int pivot_index = array[upper_bound];
    int smaller_element_index = lower_bound - 1;

    for (int current_index = lower_bound; 
         current_index < upper_bound; 
         current_index++
        ) {
        if (array[current_index] <= pivot_index) {
            smaller_element_index++;
            //using built in swap function in c++
            std::swap (array[smaller_element_index], array[current_index]);
        }
    }

    //using builtin swap function in c++
    std::swap (array[smaller_element_index + 1], array[upper_bound]);

    pivot_index = smaller_element_index + 1;
    return pivot_index;

}