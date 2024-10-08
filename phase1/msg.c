#include "./headers/msg.h"

static msg_t msgTable[MAXMESSAGES];
LIST_HEAD(msgFree_h);

void initMsgs() {
    // Initialize list head for each message and ad it to the free list
    for (int i = 0; i < MAXMESSAGES; ++i) {
        INIT_LIST_HEAD(&msgTable[i].m_list); 
        msgTable[i].m_payload = 0;                                                           
        msgTable[i].m_sender = NULL;                                                         
        list_add(&msgTable[i].m_list, &msgFree_h); 
    }    
}

void freeMsg(msg_t *m) {
    if (m) {
        if (list_empty(&m->m_list) == FALSE){
            list_del(&m->m_list); // Remove message from the list
            INIT_LIST_HEAD(&m->m_list); // Initialize the list head
        }
        
        list_add(&m->m_list, &msgFree_h); 
    }    
}

msg_t *allocMsg() {
    if (list_empty(&msgFree_h)) {
        return NULL; // No available messages
    } else {
        // Get the first entry from the list and obtain its address                         
        struct list_head *entry = msgFree_h.next;
        list_del(entry); // Remove message from msgFree list

        // reset message list
        INIT_LIST_HEAD(entry);

        // Retrieve the pointer to the actual message structure
        msg_t *m = container_of(entry, msg_t, m_list);

        // Initialize message fields
        m->m_sender = NULL;
        m->m_payload = 0;

        return m;
    }    
}

void mkEmptyMessageQ(struct list_head *head) {
    INIT_LIST_HEAD(head);                                                                   
}

int emptyMessageQ(struct list_head *head) {
    return list_empty(head);                                                                
}

void insertMessage(struct list_head *head, msg_t *m) {
    list_add_tail(&m->m_list, head);                                                        
}

void pushMessage(struct list_head *head, msg_t *m) {
    list_add(&m->m_list, head);                                                             
}

msg_t *popMessage(struct list_head *head, pcb_t *p_ptr) {
    if (p_ptr == NULL)
        return popMessageByPid(head, ANYMESSAGE);
    return popMessageByPid(head, p_ptr->p_pid);
}

msg_t *popMessageByPid(struct list_head *head, int pid) {
    struct list_head *pos;
    msg_t *msg = NULL;

    if (list_empty(head)) {
        return NULL; // Empty queue
    }

    list_for_each(pos, head) {
        msg = container_of(pos, msg_t, m_list);
        if (msg->m_sender->p_pid == pid || pid == ANYMESSAGE) {                                      
            list_del(pos); // Remove the message from the list                              
            INIT_LIST_HEAD(pos); // Initialize the list head
            freeMsg(msg); // Free the message
            return msg;
        }
    }

    return NULL; // No message found for the given sender
}

msg_t *headMessage(struct list_head *head) {
    if (list_empty(head)) {
        return NULL; // Empty queue
    }

    struct list_head *first = head->next;                                                  
    return container_of(first, msg_t, m_list);                                             
}
