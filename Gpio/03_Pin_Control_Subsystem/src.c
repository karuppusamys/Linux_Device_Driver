The following sample shows how to get a pincontrol and apply its default configuration:

struct pinctrl *p;
struct pinctrl_state *s;
int ret;

p = pinctrl_get(dev);
if (IS_ERR(p))
{
    return p;
}

s = pinctrl_lookup_state(p, name);
if (IS_ERR(s)) 
{
    devm_pinctrl_put(p);
    return ERR_PTR(PTR_ERR(s));
}

ret = pinctrl_select_state(p, s);
if (ret < 0) 
{
    devm_pinctrl_put(p);
    return ERR_PTR(ret);
}

///////////
pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
if (IS_ERR(pinctrl))
{
  dev_warn(&pdev->dev,"pins are not configured from the driver\n");
}
