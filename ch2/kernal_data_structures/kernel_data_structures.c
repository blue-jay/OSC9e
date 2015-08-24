#include <linux/list.h>
#include <linux/types.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <sys/queue.h>
struct birthday{
      int day;
      int month;
      int year;
      struct list_head list;
    };
static LIST_HEAD(birthday_list); 
  
  struct birthday *a[5];
  


/* This function is called when the module is loaded. */
int simple_init(void)
{
    int i;
  for(i= 0; i<5; i++){
    a[i] = kmalloc((sizeof *a[i]), GFP_KERNEL);
    a[i]->day = i + 1;
    a[i]->month = 5;
    a[i]->year = 1995;
    INIT_LIST_HEAD(&(a[i]->list));
    list_add_tail(&(a[i]->list),&birthday_list);
  }

  //struct list_head birthday_list;
  
  
  
  struct birthday *ptr;
  list_for_each_entry(ptr, &birthday_list, list){
    printk(KERN_INFO "\n\nborn on %d, %d, %d\n",
           ptr->year, ptr->month, ptr->day);
  }
  printk(KERN_INFO "Loading Module\n");
  return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
  struct birthday *ptr, *next;
  list_for_each_entry_safe(ptr, next, &birthday_list, list){
    list_del(&ptr->list);
    kfree(ptr);
    printk(KERN_INFO "free!");
  }
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

