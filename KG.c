#include <stdio.h>
float meters_to_kilometers(float meters);
float grams_to_kilograms(float grams);
float kilometers_to_meters(float kilometers);
float kilograms_to_grams(float kilograms);

int main() {
    int choice;
    float value, converted;

    printf("Unit Converter Program\n");
    printf("1. Convert Meters to Kilometers\n");
    printf("2. Convert Kilometers to Meters\n");
    printf("3. Convert Grams to Kilograms\n");
    printf("4. Convert Kilograms to Grams\n");
    printf("5. Exit\n");

    while (1) {
        printf("\nEnter your choice (1/2/3/4/5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value in meters: ");
                scanf("%f", &value);
                converted = meters_to_kilometers(value);
                printf("%.2f meters is equal to %.2f kilometers.\n", value, converted);
                break;

            case 2:
                printf("Enter value in kilometers: ");
                scanf("%f", &value);
                converted = kilometers_to_meters(value);
                printf("%.2f kilometers is equal to %.2f meters.\n", value, converted);
                break;

            case 3:
                printf("Enter value in grams: ");
                scanf("%f", &value);
                converted = grams_to_kilograms(value);
                printf("%.2f grams is equal to %.2f kilograms.\n", value, converted);
                break;

            case 4:
                printf("Enter value in kilograms: ");
                scanf("%f", &value);
                converted = kilograms_to_grams(value);
                printf("%.2f kilograms is equal to %.2f grams.\n", value, converted);
                break;

            case 5:
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please choose between 1 and 5.\n");
        }
    }

    return 0;
}
float meters_to_kilometers(float meters) {
    return meters / 1000.0;
}
float kilometers_to_meters(float kilometers) {
    return kilometers * 1000.0;
}
float grams_to_kilograms(float grams) {
    return grams / 1000.0;
}
float kilograms_to_grams(float kilograms) {
    return kilograms * 1000.0;
}
