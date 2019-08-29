//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_MESSAGELIST_H
#define GTKMM_MESSAGELIST_H

#include <gtkmm.h>

class MessageList: public Gtk::ScrolledWindow{
public:
    MessageList();
    virtual ~MessageList();

    void insert(){

    }

protected:
class MessageColumns : public Gtk::TreeModel::ColumnRecord{
public:
    Gtk::TreeModelColumn<Glib::ustring> content;
    Gtk::TreeModelColumn<Glib::ustring> nickName;
    Gtk::TreeModelColumn<unsigned int> id;
    Gtk::TreeModelColumn<Glib::ustring> bt;
    int size=0;
    MessageColumns(){
        add(id);
        add(nickName);
        add(content);
        add(bt);
        size=4;
    }
}messageColumns;

Gtk::TreeView treeView;
Glib::RefPtr<Gtk::ListStore> refTreeModel;

};

#endif //GTKMM_MESSAGELIST_H
