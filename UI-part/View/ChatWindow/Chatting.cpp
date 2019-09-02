//
// Created by ervinxie on 8/29/19.
//

#include "../implement.h"

Chatting::Chatting() : chatName("ChatEntity") {
    set_size_request(400, 500);

    Gtk::Frame *chatNameFrame = Gtk::manage(new Gtk::Frame);
    Gtk::HBox *chatNameAndDetail = Gtk::manage(new Gtk::HBox);


    chatNameAndDetail->pack_start(chatName, Gtk::PACK_SHRINK);
    chatNameAndDetail->pack_end(chatDetailBt, Gtk::PACK_SHRINK);
    chatDetailBt.set_halign(Gtk::ALIGN_END);
    chatDetailBt.set_image_from_icon_name("format-justify-fill");
    chatDetailBt.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        dialog.get_content_area()->pack_start(*Gtk::manage(new ContactInfo), Gtk::PACK_SHRINK);
        dialog.add_button("OK", 0);

        dialog.show_all_children();
        dialog.run();
    });
    chatNameFrame->add(*chatNameAndDetail);

    chatName.set_padding(10, 10);
    pack_start(*chatNameFrame, Gtk::PACK_SHRINK);


    msgList.set_vexpand(true);
    msgList.set_valign(Gtk::ALIGN_FILL);

    msgList.append_column("Avatar",message.senderAvatar);
    msgList.append_column("content",message.content);
    msgList.set_headers_visible(false);

    messages = Gtk::ListStore::create(message);
    filter = Gtk::TreeModelFilter::create(messages);
    msgList.set_model(filter);

    for(int i=0;i<100;i++){
        auto row = (*messages->append());
        row[message.content]="\nHello!"+std::to_string(i)+"\n";


        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(32, 32, Gdk::INTERP_BILINEAR);
        row[message.senderAvatar] = ava;
    }




    scrolledWindow.add(msgList);
    scrolledWindow.set_vexpand(true);
    scrolledWindow.set_valign(Gtk::ALIGN_FILL);
    pack_start(scrolledWindow);





    pack_start(tools, Gtk::PACK_SHRINK);
    expressionBt.set_image_from_icon_name("face-smile");
    fileBt.set_image_from_icon_name("document-open");
    fileBt.signal_clicked().connect([this] {
        Gtk::FileChooserDialog fileChooserDialog("");
        fileChooserDialog.add_button("OK", 0);
        fileChooserDialog.add_button("Cancel", 1);
        fileChooserDialog.run();
    });

    tools.pack_start(expressionBt, Gtk::PACK_SHRINK);
    tools.pack_start(fileBt, Gtk::PACK_SHRINK);


    Gtk::Frame *msgEditFrame = Gtk::manage(new Gtk::Frame);
    msgEditFrame->add(msgEdit);
    msgEditFrame->set_border_width(0);
    pack_start(*msgEditFrame, Gtk::PACK_SHRINK);

    refMsgText = Gtk::TextBuffer::create();
    msgEdit.set_buffer(refMsgText);
    msgEdit.set_size_request(100, 100);

    show_all_children();
}

Chatting::~Chatting() {

}
