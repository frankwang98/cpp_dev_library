package org.example;

class Main {
    public static void main(String[] argv) {
        System.out.println("hello world");

        MyClass myObj = new MyClass();
        myObj.someMethod();

        int result = myObj.addNumbers(5, 10);
        System.out.println("result: " + result);

    }
}