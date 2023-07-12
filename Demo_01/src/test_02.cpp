/**
* Created by WuXiangGuJun on 2023/4/7.
*/
#include <iostream>
#include <map>

class ChatDialog {
public:
    void activate() {

    }
};

std::map<int64_t, ChatDialog *> m_ChatDialogs;

void onDoubleClickFriendItem(int64_t userid) {
    auto targetChatDialog = m_ChatDialogs.find(userid);
    //好友对话框不存在，则创建它并激活
    if (targetChatDialog == m_ChatDialogs.end()) {
        ChatDialog *p_ChatDialog = new ChatDialog();
        m_ChatDialogs.insert(std::pair<int64_t, ChatDialog *>(userid, p_ChatDialog));
        p_ChatDialog->activate();
    } else {
        targetChatDialog->second->activate();
    }
}

void onDoubleClickFriendItem2(int64_t userid) {
    auto [iter, inserted] = m_ChatDialogs.try_emplace(userid);
    if (inserted) {
        iter->second->activate();
    }
    iter->second->activate();
}


int main() {
    onDoubleClickFriendItem(906106643L);
}