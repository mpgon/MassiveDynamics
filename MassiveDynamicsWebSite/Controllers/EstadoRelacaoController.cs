using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using SocialGameWebSite.Models;
using MassiveDynamicsWebSite.Models;

namespace SocialGameWebSite.Controllers
{
    public class EstadoRelacaoController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();

        // GET: /EstadoRelacao/
        public ActionResult Index()
        {
            var estadorelacao = db.EstadoRelacao.Include(e => e.jogo);
            return View(estadorelacao.ToList());
        }

        // GET: /EstadoRelacao/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            EstadoRelacao estadorelacao = db.EstadoRelacao.Find(id);
            if (estadorelacao == null)
            {
                return HttpNotFound();
            }
            return View(estadorelacao);
        }

        // GET: /EstadoRelacao/Create
        public ActionResult Create()
        {
            ViewBag.jogoID = new SelectList(db.Jogo, "ID", "nome");
            return View();
        }

        // POST: /EstadoRelacao/Create
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(EstadoRelacao estadorelacao)
        {
            if (ModelState.IsValid)
            {
                db.EstadoRelacao.Add(estadorelacao);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.jogoID = new SelectList(db.Jogo, "ID", "nome", estadorelacao.jogoID);
            return View(estadorelacao);
        }

        // GET: /EstadoRelacao/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            EstadoRelacao estadorelacao = db.EstadoRelacao.Find(id);
            if (estadorelacao == null)
            {
                return HttpNotFound();
            }
            ViewBag.jogoID = new SelectList(db.Jogo, "ID", "nome", estadorelacao.jogoID);
            return View(estadorelacao);
        }

        // POST: /EstadoRelacao/Edit/5
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(EstadoRelacao estadorelacao)
        {
            if (ModelState.IsValid)
            {
                db.Entry(estadorelacao).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.jogoID = new SelectList(db.Jogo, "ID", "nome", estadorelacao.jogoID);
            return View(estadorelacao);
        }

        // GET: /EstadoRelacao/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
				return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            EstadoRelacao estadorelacao = db.EstadoRelacao.Find(id);
            if (estadorelacao == null)
            {
                return HttpNotFound();
            }
            return View(estadorelacao);
        }

        // POST: /EstadoRelacao/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            EstadoRelacao estadorelacao = db.EstadoRelacao.Find(id);
            db.EstadoRelacao.Remove(estadorelacao);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
