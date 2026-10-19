/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* result = &dummy;
        ListNode* back = &dummy;

        if (!list1) return list2;
        if (!list2) return list1;

        while (list1 && list2){
            if (list1->val <= list2->val){
                
                result->next = new ListNode(list1->val);
                result = result->next;
                list1 = list1->next;

            }else{

                result->next = new ListNode(list2->val);
                result = result->next;
                list2 = list2->next;

            }
        }

        if (list1)
            result->next = list1;
        else if(list2)
            result->next = list2;

        return back->next;
    }
};

// note : 当用指针题想要用一个指针表示链表始终推进，一个表示其原位置时可以先共同使用一个空的头：
// ListNode dummy(0); ListNode* list1 = &dummy; list2...
// 当构造函数构造值而需要该新值指针时可直接在构造函数之前加一个 new
// @lc code=end

