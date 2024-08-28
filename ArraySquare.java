public class ArraySquare {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};

        System.out.println("Original Array:");
        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }

        System.out.println("\n\nSquared Array:");
        for (int i = 0; i < numbers.length; i++) {
            int square = numbers[i] * numbers[i];
            System.out.print(square + " ");
        }
    }
}
