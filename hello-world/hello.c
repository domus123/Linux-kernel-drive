#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kernel.h> 

MODULE_LICENSE("Free for use");
MODULE_AUTHOR("Lucas Guerra - LINA - 2016");

static int hello_init(void) {
  
  printk(KERN_ALERT "Hello, world \n") ;
  return 0;   

}


static void hello_exit(void) {
  
  printk(KERN_ALERT "Goodbye\n");

}

module_init(hello_init); /* Special macro to define init and exit for thin module */
module_exit(hello_exit);
