/*
 Copyright (C) 2016 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <myhtml/api.h>

int main(int argc, const char * argv[])
{
    // basic init
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    printf("Init tree\n");
    
    // init tree
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_encoding_set(tree, MyHTML_ENCODING_UTF_8);
    
    // create nodes
    printf("Create DIV element\n");
    myhtml_tree_node_t* base_node = myhtml_node_create(tree, MyHTML_TAG_DIV, MyHTML_NAMESPACE_HTML);
    myhtml_node_insert_to_appropriate_place(tree, myhtml_tree_get_document(tree), base_node);
    
    printf("Create and append to DIV element 100 000 P elements\n");
    char tmp_buf_key[128];
    char tmp_buf_value[128];
    char tmp_buf_text[128];
    
    for (size_t i = 1; i < 100001; i++) {
        myhtml_tree_node_t* new_p_node = myhtml_node_create(tree, MyHTML_TAG_P, MyHTML_NAMESPACE_HTML);
        myhtml_node_append_child(tree, base_node, new_p_node);
        
        myhtml_tree_node_t* new_text_node = myhtml_node_create(tree, MyHTML_TAG__TEXT, MyHTML_NAMESPACE_HTML);
        myhtml_node_append_child(tree, new_p_node, new_text_node);
        
        sprintf(tmp_buf_key, "best_key_for_%zu", i);
        sprintf(tmp_buf_value, "for best value %zu", i);
        sprintf(tmp_buf_text, "Text! Entity &#x26;#%zu = &#%zu", i, i);
        
        myhtml_node_text_set_with_charef(tree, new_text_node,
                             tmp_buf_text, strlen(tmp_buf_text), MyHTML_ENCODING_UTF_8);
        
        myhtml_attribute_add(tree, new_p_node,
                             tmp_buf_key, strlen(tmp_buf_key),
                             tmp_buf_value, strlen(tmp_buf_value), MyHTML_ENCODING_UTF_8);
    }
    
    // print
    printf("Print result:\n");
    myhtml_tree_print_node_children(tree, myhtml_tree_get_document(tree), stdout, 0);
    
    // release resources
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    
    return 0;
}


