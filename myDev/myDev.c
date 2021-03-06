#include <linux/module.h> 
#include <linux/string.h> 
#include <linux/fs.h> 
#include <asm/uaccess.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lina device driver");
MODULE_AUTHOR("Lucas Guerra ");

static char msg[100] ={0}; 
static short readPos = 0; 
static int times = 0;

static int dev_open (struct inode *, struct file *);
static int dev_rls (struct inode *, struct file *);
static ssize_t dev_read (struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);


/* Estrutura que contem todas as funçoes utilizadas*/
static struct file_operations fops = {
  
  .read = dev_read,
  .open = dev_open,
  .write = dev_write,
  .release = dev_rls,

};


/* Main */
int init_module(void) {
  
  int t = register_chrdev(89, "myDev", &fops) ; /* Funçao usada para registrar driver */

  if (t < 0) /* nao foi possivel registrar driver */
    printk(KERN_ALERT "Device registration failed .. \n");
  else 
    printk(KERN_ALERT "Device registered ... \n");
  return t;

}

void cleanup_module(void){ 
  
  unregister_chrdev( 89,"myDev");

}

/* Chamada na abertura */
static int dev_open (struct inode *inod, struct file *fil) { 
  
  times++; 
  printk(KERN_ALERT "Device opened %d times .... \n", times); 
  return 0;
  
}

static ssize_t dev_read (struct file *filp, char *buff, size_t len, loff_t *off) {

  short count = 0;
  while (len && (msg[readPos] != 0) ) { 
    put_user(msg[readPos], buff++); /*Copia do kernel para area de usuario */ 
    count++; 
    len--; 
    readPos++;
  }
  return count;
}

static ssize_t dev_write (struct file *filp,const char *buff, size_t len, loff_t *off) {

  short ind = len - 1;
  short count = 0; 
  memset(msg, 0, 100); /* Reseta a string */ 
  readPos = 0;
  while(len > 0) {
    msg[count++] = buff[ind--]; /* Revertendo o a string salva no buffer */ 
    len--;
  }
  //  msg[count] = '\n'; 
  return count; 

}


static int dev_rls(struct inode *inod, struct file *fil) {
  
  printk(KERN_ALERT "Device closed\n"); 
  return 0; 

}




