//
// Created by ervinxie on 8/28/19.
//

#include "MessageList.h"

MessageList::MessageList() {
    set_size_request(200, 300);
    add(treeView);
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    refTreeModel = Gtk::ListStore::create(messageColumns);
    treeView.set_model(refTreeModel);

    //Fill the TreeView's model
    Gtk::TreeModel::Row row = *(refTreeModel->append());
    row[messageColumns.id] = 1;
    row[messageColumns.nickName] = "What";
    row[messageColumns.content] = "Hello";
    row[messageColumns.bt] = "asdfasdf";

    treeView.append_column("NickName", messageColumns.nickName);
    treeView.append_column("Content", messageColumns.content);
    treeView.append_column("ID", messageColumns.id);
    treeView.append_column("Bt", messageColumns.bt);


    for (int i = 0; i < messageColumns.size; i++) {
        auto column = treeView.get_column(i);
        column->set_reorderable();
    }
    treeView.get_column(0)->set_visible(false);
    show_all_children();
}

MessageList::~MessageList() {}

