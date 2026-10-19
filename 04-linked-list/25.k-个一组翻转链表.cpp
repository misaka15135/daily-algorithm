/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k < 2) {
            return head;
        }

        ListNode dummy(0);
        ListNode* result = &dummy;
        ListNode* back = &dummy;
        ListNode* kth;

        while (nowEnough(head, k, kth)) {
            ListNode* next1 = kth->next;
            result->next = reverse4n(head, k);
            head->next = next1;
            head = head->next;
            for (int i = 0; i < k; i++) {
                result = result->next;
            }
        }

        return back->next;
    }

    bool nowEnough(ListNode* head, int n, ListNode*& kth) {
        bool enough = true;

        ListNode* temp = head;

        for (int i = 0; i < n; i++) {
            if (!temp) {
                enough = false;
                break;
            }else {
                kth = temp;
                temp = temp->next; 
            }
        }

        return enough;
    }

    ListNode* reverse4n(ListNode* head, int n) {
        ListNode* p = head;
        ListNode* q = head->next;
        ListNode* temp;

        for (int i = 0; i < n - 1; i++) {
            temp = q->next;
            q->next = p;
            p = q;
            q = temp;
        }

        return p;
    }
};

// note ： 使用三指针反转链表时，要注意将第一个节点的next准确设置
// 一个指针等于另一个指针后，这个指针改变自己的位置不会影响原指针的位置，因为声明新指针时只是取得原指针的值，而这两个指针实际上是单独的个体
// @lc code=end

