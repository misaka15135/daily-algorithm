/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {


        ListNode* p = head;
        ListNode* q = head;

        for (int i = 0; i <= n; i++){
            if (!p) return head->next;

            p = p->next;
        }

        while (p){
            p = p->next;
            q = q->next;
        }

        q->next = q->next->next;

        return head;
    }
};

// note : 太久没用，list怎么用忘了，这题用来复健一下，看一下list怎么写
// @lc code=end

