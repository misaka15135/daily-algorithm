/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0);
        ListNode* result = &dummy;
        ListNode* back = &dummy;

        if (lists.empty()) return back->next;

        bool over = false;

        while (!over) {

            over = true;

            int temp = -1;

            for (int i = 0; i < lists.size(); i++) {

                if (over && lists[i]) {
                    over = false;
                    temp = i;
                }
                if (!over && lists[i] && (lists[i]->val < lists[temp]->val)) {
                    temp = i;
                }
            }

            if (temp != -1) {
                    result->next = lists[temp];
                    result = result->next;
                    lists[temp] = lists[temp]->next;
            }
        }
        
        return back->next;

    }
};

// note : 对指针类型解引用前一定要先判是否非空，要注意for循环中变量放置的位置
// @lc code=end

