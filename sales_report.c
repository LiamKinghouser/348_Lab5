#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    float monthSales;
    int monthIndex;
} sales_pair;


sales_pair get_minimum_sales(float sales[12]) {
    // Initialize the struct and assume the first month (index 0) has the minimum sales
    sales_pair result;
    result.monthSales = sales[0];
    result.monthIndex = 0;

    // Iterate over the rest of the array
    for (int i = 1; i < 12; i++) {
        if (sales[i] < result.monthSales) {
            // Update if a smaller value is found
            result.monthSales = sales[i];
            result.monthIndex = i;
        }
    }

    // Return the struct with both minimum value and index
    return result;
}


sales_pair get_maximum_sales(float sales[12]) {
    // Initialize the struct and assume the first month (index 0) has the maximum sales
    sales_pair result;
    result.monthSales = sales[0];
    result.monthIndex = 0;

    // Iterate over the rest of the array
    for (int i = 1; i < 12; i++) {
        if (sales[i] > result.monthSales) {
            // Update if a larger value is found
            result.monthSales = sales[i];
            result.monthIndex = i;
        }
    }

    // Return the struct with both maximum value and index
    return result;
}


float get_total_sales(float sales[12], int first_month, int last_month) {
    float total_sales = 0.0;
    for (int i = first_month; i < last_month; i++) {
        total_sales += sales[i];
    }

    return total_sales;
}


void print_reports(float sales[12]) {
    // Initialize months array
    char *months[12] = {
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"
    };

    // Print header
    printf("Monthly Sales Report for 2024\n");
    printf("\n");
    printf("Month       Sales\n");

    // Iterate through months, printing month name and sales amount
    for (int i = 0; i < 12; i++) {
        int month_length = strlen(months[i]);

        printf("%s", months[i]);
        
        for (int i = 0 ; i < (12 - month_length); i++) {
            printf(" ");
        }

        printf("%2.2f\n", sales[i]);
    }

    printf("\n");

    printf("Sales summary report:\n\n");

    // Calculate min, max, and average sales
    sales_pair min_sales = get_minimum_sales(sales);
    sales_pair max_sales = get_maximum_sales(sales);
    float average_sales = (get_total_sales(sales, 0, 12)) / 12;

    // Print min, max, and average sales
    printf("Minimum sales: %2.2f (%s)\n", min_sales.monthSales, months[min_sales.monthIndex]);
    printf("Maximum sales: %2.2f (%s)\n", max_sales.monthSales, months[max_sales.monthIndex]);
    printf("Average sales: %2.2f\n\n", average_sales);

    // Moving average report header
    printf("Six-Month moving average report:\n\n");

    for (int i = 0; i < 7; i++) { // Iterate only through the first 7 months to allow 6-month ranges
        int first_month_index = i;
        int last_month_index = i + 5; // Last month should be at `i + 5` for 6 months total

        printf("%s-%s", months[first_month_index], months[last_month_index]);

        int length = strlen(months[first_month_index]) + strlen(months[last_month_index]) + 1;

        // Adjust spacing to align the columns
        for (int j = 0; j < (18 - length); j++) {
            printf(" ");
        }

        // Calculate the average for the 6-month period
        float average = get_total_sales(sales, first_month_index, last_month_index + 1) / 6; // +1 because the range is inclusive of last month

        printf("%2.2f\n", average);
    }

    // Create an array of indices for sorting
    int indices[12];
    for (int i = 0; i < 12; i++) {
        indices[i] = i;
    }

    // Bubble sort to sort sales in descending order and maintain the month indices
    for (int i = 0; i < 12 - 1; i++) {
        for (int j = 0; j < 12 - i - 1; j++) {
            if (sales[indices[j]] < sales[indices[j + 1]]) {
                // Swap the indices
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf("\n");

    printf("Sales report (highest to lowest):\n\n");
    printf("Month       Sales\n");
    
    for (int i = 0; i < 12; i++) {
        printf("%-12s $%2.2f\n", months[indices[i]], sales[indices[i]]);
    }
}

int main() {
    // Open input file in read mode
    FILE *sales_file = fopen("sales.txt", "r");

    float sales[12];
    int c;

    char current_figure[100];

    int index = 0;
    int char_index = 0;

    // If sales file exists, read data from file into arrays
    if (sales_file) {
        while ((c = getc(sales_file)) != EOF) {
            if (c != '\n') {
                current_figure[char_index] = (char)c;
                char_index += 1;
            }
            else {
                sales[index] = atof(current_figure);
                index += 1;
                char_index = 0;
            }
        }
        fclose(sales_file);
    }

    if (char_index > 0) {
        current_figure[char_index] = '\0';
        sales[index] = atof(current_figure);
    }

    // Print sales report
    print_reports(sales);


    return 0;
}