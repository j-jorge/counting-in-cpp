#include <libxml/tree.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlsave.h>

#include <iostream>

namespace
{
  struct xmlFreeDeleter
  {
    void operator()(const void* p) const
    {
      xmlFree((void*)p);
    }
  };
}

template<typename T>
using xml_ptr = std::unique_ptr<T, xmlFreeDeleter>;

static xmlNodePtr process_body(xmlNodePtr node);

static const xmlChar* operator""_xml(const char* s, size_t n)
{
  return (const xmlChar*)s;
}

static void dump(xmlNodePtr n)
{
  xmlBufferPtr buffer = xmlBufferCreate();
  int size = xmlNodeDump(buffer, nullptr, n, 0, 1);
  std::cout << "++\n" << buffer->content << "--\n" << std::endl;
}

static xmlNodePtr remove_node(xmlNodePtr node)
{
  const xmlNodePtr n = node;
  node = node->next;
  xmlUnlinkNode(n);
  xmlFreeNode(n);

  return node;
}

static void process_head(xmlNodePtr node)
{
  xmlNodePtr child = node->children;

  while (child != nullptr)
    {
      if (xmlStrEqual(child->name, "link"_xml)
          && xmlStrEqual
          (xml_ptr<xmlChar>(xmlGetProp(child, "type"_xml)).get(),
           "text/css"_xml))
        child = remove_node(child);
      else
        child = child->next;
    }

  const xmlNodePtr link =
    xmlNewChild(node, nullptr, "link"_xml, nullptr);

  xmlNewProp(link, "rel"_xml, "stylesheet"_xml);
  xmlNewProp(link, "type"_xml, "text/css"_xml);
  xmlNewProp(link, "href"_xml, "style.css"_xml);
}

static void process_pre(xmlNodePtr node)
{
  xmlNodePtr child = node->children;

  while (child != nullptr)
    {
      if (xmlStrEqual
          (xml_ptr<const xmlChar>(xmlGetProp(child, "style"_xml)).get(),
           "color:#D35212"_xml))
        xmlNewProp(child, "class"_xml, "highlighted-code"_xml);

      const xmlAttrPtr style = xmlHasProp(child, "style"_xml);

      if (style)
        xmlRemoveProp(style);

      const xml_ptr<xmlChar> css_class(xmlGetProp(child, "class"_xml));

      if (xmlStrEqual(css_class.get(), "label"_xml))
        child = remove_node(child);
      else if (xmlStrEqual(child->name, "span"_xml)
               && (child->content == nullptr)
               && (child->properties == nullptr)
               && (xmlChildElementCount(child) == 1)
               && (child->children->type == xmlElementType::XML_ELEMENT_NODE))
        {
          xmlNodePtr n = child->children;
          xmlReplaceNode(child, n);
          child = n->next;
        }
      else
        child = child->next;
    }
}

static xmlNodePtr transform_enumerate(xmlNodePtr node)
{
  const xmlNodePtr ol = xmlNewNode(nullptr, "ol"_xml);

  xmlNodePtr child = node->children;

  while (child != nullptr)
    {
      if (xmlStrEqual(child->name, "dt"_xml))
        {
          if (xmlStrEqual(child->children->content, "a."_xml))
            xmlNewProp(ol, "type"_xml, "a"_xml);

          child = remove_node(child);
          break;
        }

      child = child->next;
    }

  while (child != nullptr)
    {
      if (xmlStrEqual(child->name, "dt"_xml))
        child = remove_node(child);
      else if (xmlStrEqual(child->name, "dd"_xml))
        {
          const xmlNodePtr li = xmlNewNode(nullptr, "li"_xml);
          xmlAddChildList(li, child->children);
          child->children = nullptr;

          xmlAddChild(ol, li);
          child = child->next;
        }
      else
        child = child->next;
    }

  xmlReplaceNode(node, ol);

  return ol;
}

static xmlNodePtr process_dl(xmlNodePtr node)
{
  if (xmlStrEqual
      (xml_ptr<xmlChar>(xmlGetProp(node, "class"_xml)).get(),
       "enumerate-enumitem"_xml))
    return transform_enumerate(node);

  return node;
}

static int table_of_contents_level(const xmlChar* css_class)
{
  using pair = std::pair<const xmlChar*, int>;
  const pair sections[] =
    {
      {"chapter"_xml, 0},
      {"section"_xml, 1},
      {"subsection"_xml, 2},
      {"subsubsection"_xml, 3},
      {"likechapter"_xml, 0},
    };

  for (const pair& p : sections)
    if (xmlStrncmp(css_class, p.first, xmlStrlen(p.first)) == 0)
      return p.second;

  return 0;
}

static int table_of_contents_level(xmlNodePtr node)
{
  return table_of_contents_level
    (xml_ptr<const xmlChar>(xmlGetProp(node, "class"_xml)).get());
}

static xmlNodePtr process_table_of_contents
(xmlNodePtr ul, xmlNodePtr node, int root_level)
{
  while (node != nullptr)
    {
      if (!xmlStrEqual(node->name, "span"_xml))
        {
          node = node->next;
          continue;
        }

      const int level = table_of_contents_level(node);

      if (level < root_level)
        return node;

      if (level == root_level)
        {
          const xmlNodePtr li = xmlNewNode(nullptr, "li"_xml);
          xmlAddChild(ul, li);

          const xmlNodePtr next = node->next;
          xmlRemoveProp(xmlHasProp(node, "class"_xml));
          xmlUnlinkNode(node);
          xmlAddChild(li, node);

          node = next;
        }
      else
        {
          const xmlNodePtr sub = xmlNewNode(nullptr, "ul"_xml);

          node = process_table_of_contents(sub, node, level);
          xmlAddChild(ul, sub);
        }
    }

  return nullptr;
}

static xmlNodePtr process_table_of_contents(xmlNodePtr node, int level)
{
  const xmlNodePtr ul = xmlNewNode(nullptr, "ul"_xml);

  xmlNodePtr next = process_table_of_contents(ul, node->children, level);
  xmlReplaceNode(node, ul);

  if (next != nullptr)
    process_table_of_contents(ul, next, table_of_contents_level(next));

  return ul;
}

static xmlNodePtr process_p(xmlNodePtr node)
{
  if (node->children == nullptr)
    return remove_node(node);

  xmlNodePtr child = node->children;

  while (child && !xmlStrEqual(child->name, "span"_xml))
    child = child->next;

  if (!child)
    return process_body(node)->next;

  const xml_ptr<const xmlChar> child_class
    (xmlGetProp(child, "class"_xml));

  // CSS class for the main title.
  if (!xmlStrEqual(child_class.get(), "ptmb8t-x-x-248"_xml))
    return process_body(node)->next;

  xmlChar* title = xmlStrdup(xmlNodeGetContent(child));

  for (child = child->next; child; child = child->next)
    if (xmlStrEqual(child->name, "span"_xml))
      {
        title = xmlStrcat(title, " "_xml);
        title = xmlStrcat(title, xmlNodeGetContent(child));
      }

  xmlNodePtr title_node = xmlNewNode(nullptr, "header"_xml);
  xmlAddChild(title_node, xmlNewDocText(nullptr, title));

  xmlFree(title);
  xmlReplaceNode(node, title_node);

  return title_node->next;
}

static xmlNodePtr process_body(xmlNodePtr node)
{
  xmlNodePtr child = node->children;
  xmlNodePtr last_pre = nullptr;
  int pre_count = 0;

  while (child != nullptr)
    {
      if (xmlStrEqual(child->name, "pre"_xml))
        {
          process_pre(child);
          ++pre_count;

          if (last_pre)
            {
              if (pre_count == 2)
                {
                  const xmlNodePtr span = xmlNewNode(nullptr, "span"_xml);
                  xmlNewProp(span, "class"_xml, "highlighted-code"_xml);
                  xmlAddChildList(span, child->children);
                  xmlAddChild(last_pre, span);
                }
              else
                xmlAddChildList(last_pre, child->children);

              child->children = nullptr;
              child = remove_node(child);
            }
          else
            {
              last_pre = child;
              child = child->next;
            }
        }
      else if (xmlStrEqual(child->name, "p"_xml))
        {
          child = process_p(child);
          last_pre = nullptr;
        }
      else if (xmlStrEqual(child->name, "br"_xml))
        {
          child = remove_node(child);
          last_pre = nullptr;
        }
      else
        {
          const xml_ptr<const xmlChar> css_class
            (xmlGetProp(child, "class"_xml));

          if (xmlStrEqual(css_class.get(), "tableofcontents"_xml)
              || xmlStrstr(css_class.get(), "TOCS"_xml))
            {
              child =
                process_table_of_contents
                (child, table_of_contents_level(css_class.get()));
              xmlNewProp(child, "class"_xml, "table-of-contents"_xml);

              child = child->next;
            }
          else
            {
              if (last_pre && (child->type != xmlElementType::XML_TEXT_NODE))
                {
                  const xmlNodePtr code = xmlNewNode(nullptr, "code"_xml);

                  xmlNewProp(code, "class"_xml, "language-c++"_xml);
                  xmlNewProp(code, "data-lang"_xml, "c++"_xml);

                  xmlAddChildList(code, last_pre->children);
                  last_pre->children = nullptr;
                  xmlAddChild(last_pre, code);

                  last_pre = nullptr;
                  pre_count = 0;
                }

              if (xmlStrEqual(child->name, "dl"_xml))
                child = process_dl(child);
              else
                child = process_body(child);

              child = child->next;
            }
        }
    }

  return node;
}

static void process_html(xmlNodePtr node)
{
  node = node->children;

  while (node != nullptr)
    {
      if (xmlStrEqual(node->name, "head"_xml))
        process_head(node);
      else if (xmlStrEqual(node->name, "body"_xml))
        process_body(node);

      node = node->next;
    }
}

int main(int argc, char** argv)
{
  int exit_code = 0;

  for (int i = 1; i != argc; ++i)
    {
      std::cerr << "Processing '" << argv[i] << "'\n";
      xmlDocPtr document =
        xmlReadFile
        (argv[i], "utf-8",
         xmlParserOption::XML_PARSE_RECOVER
         | xmlParserOption::XML_PARSE_NONET
         );

      if (document == nullptr)
        {
          std::cerr << "Could not parse '" << argv[i] << "'\n";
          exit_code = 1;
          continue;
        }

      xmlNodePtr root = xmlDocGetRootElement(document);
      xmlNodePtr node = root;

      while ((node != nullptr)
             && !xmlStrEqual(node->name, "html"_xml))
        node = node->next;

      if (node == nullptr)
        std::cerr << argv[i] << ": no html node\n";
      else
        process_html(node);

      xmlSaveCtxtPtr const save =
        xmlSaveToFilename
        (argv[i], "utf-8",
         xmlSaveOption::XML_SAVE_AS_HTML);

      if (save == nullptr)
        exit_code = 1;
      else if (xmlSaveTree(save, root) == -1)
        exit_code = 1;

      xmlSaveClose(save);
    }

  return exit_code;
}
