// user/testmp.c

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char *test_name = "";
int tests_passed = 0;
int tests_failed = 0;

void print_test_result(int condition, char *msg) {
    if (condition) {
        printf("PASS: %s - %s\n", test_name, msg);
        tests_passed++;
    } else {
        printf("FAIL: %s - %s\n", test_name, msg);
        tests_failed++;
    }
}

void test_basic_protection() {
    test_name = "test_basic_protection";
    char *addr = sbrk(4096); // Allocate one page
    
    // Ensure allocation succeeded
    if (addr == (char*)-1) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    // Write initial value
    *addr = 'A';
    
    // Protect the page
    int ret = mprotect(addr, 1);
    print_test_result(ret == 0, "mprotect succeeded");
    
    // Try to write (should cause page fault)
    int pid = fork();
    if (pid == 0) {
        printf("Child trying to write to protected memory...\n");
        *addr = 'B'; // This should cause a page fault
        exit(0);     // Should not reach here
    } else {
        int status;
        wait(&status);
        // El proceso hijo debería haber terminado con error
        print_test_result(status != 0, "Write to protected memory caused fault");
    }
    
    // Verify original value wasn't changed
    print_test_result(*addr == 'A', "Protected memory value unchanged");
    
    // Unprotect and try writing again
    ret = munprotect(addr, 1);
    print_test_result(ret == 0, "munprotect succeeded");
    
    *addr = 'C';
    print_test_result(*addr == 'C', "Write after unprotect succeeded");
}

void test_invalid_params() {
    test_name = "test_invalid_params";
    char *addr = sbrk(4096);
    
    // Test unaligned address
    int ret = mprotect(addr + 100, 1);
    print_test_result(ret == -1, "Unaligned address rejected");
    
    // Test invalid length
    ret = mprotect(addr, 0);
    print_test_result(ret == -1, "Zero length rejected");
    
    ret = mprotect(addr, -1);
    print_test_result(ret == -1, "Negative length rejected");
    
    // Test invalid address
    ret = mprotect((char*)0x1000000, 1);
    print_test_result(ret == -1, "Invalid address rejected");
}

void test_multiple_pages() {
    test_name = "test_multiple_pages";
    int pages = 3;
    char *addr = sbrk(4096 * pages);
    
    // Initialize pages
    for(int i = 0; i < pages; i++) {
        addr[i * 4096] = 'A' + i;
    }
    
    // Protect multiple pages
    int ret = mprotect(addr, pages);
    print_test_result(ret == 0, "Protected multiple pages");
    
    // Fork and try to write
    int pid = fork();
    if(pid == 0) {
        addr[4096] = 'X'; // Try to write to second page
        exit(0);          // Should not reach here
    } else {
        int status;
        wait(&status);
        print_test_result(status != 0, "Write to middle page caused fault");
    }
    
    // Verify all values unchanged
    int unchanged = 1;
    for(int i = 0; i < pages; i++) {
        if(addr[i * 4096] != 'A' + i) unchanged = 0;
    }
    print_test_result(unchanged, "All pages remained protected");
}

int main(int argc, char *argv[]) {
    printf("Starting mprotect/munprotect tests...\n\n");
    
    test_basic_protection();
    test_invalid_params();
    test_multiple_pages();
    
    printf("\nTest Summary:\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    
    exit(tests_failed); // Return number of failed tests as exit code
}
