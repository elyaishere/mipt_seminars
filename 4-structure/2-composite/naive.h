#pragma once

class Node;
class Config;
class FilterList;

class FilterManager {
public:
    FilterManager(const Config&);
    void ParseFilterListFromConfig(FilterList&);

private:
    const Node* param_types;
    const Node* param_names;
    const Node* handler_states;
    const Node* handler_flags;
    const Node* handler_param_ops;
    const Node* handler_param_ids;
    const Node* handler_filters;
    const Node* handler_flt_ops;
    const Node* handler_flt_flags;
};
